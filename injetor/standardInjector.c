#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef BOOL (_stdcall *EnumProcesses)(DWORD *processesID, DWORD cb, LPDWORD byteSize);
typedef DWORD (_stdcall *EnumProcessModules)(HANDLE hProcess, HMODULE *hModules, DWORD hmSize, LPDWORD byteSize);
typedef DWORD (_stdcall *GetModuleBaseNameA)(HANDLE hProcess, HMODULE hModule, LPSTR baseName, DWORD bnSize);

void ErrorMessage(const char *message){
    fprintf(stderr, message);
    exit(EXIT_FAILURE);
}

DWORD FindProcessID(HMODULE psapiLib, const char *pName){
    EnumProcesses enumProcs = (EnumProcesses)GetProcAddress(psapiLib, "EnumProcesses");
    EnumProcessModules enumModules = (EnumProcessModules)GetProcAddress(psapiLib, "EnumProcessModules");
    GetModuleBaseNameA getBaseName = (GetModuleBaseNameA)GetProcAddress(psapiLib, "GetModuleBaseNameA");
    if(! enumProcs) ErrorMessage("Error finding EnumProcesses from psapi.dll\n");
    if(! enumModules) ErrorMessage("Error finding EnumProcessModules from psapi.dll\n");
    if(! getBaseName) ErrorMessage("Error finding GetModuleBaseNameA from psapi.dll\n");

    DWORD procs[1024], byteSize, size;
    unsigned int i;

    if(! enumProcs(procs, sizeof(procs), &byteSize)) ErrorMessage("Error running EnumProcesses\n");

    size = byteSize / sizeof(DWORD);

    DWORD pID = 0;
    for(i = 0; i < size & !pID; i++){
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, procs[i]);

        if(hProcess){
            HMODULE hModule;
            DWORD byteSize, resp;
            LPSTR name;
            name = malloc(300 * sizeof(LPSTR));

            resp = enumModules(hProcess, &hModule, sizeof(hModule), &byteSize);
            if(resp){
                getBaseName(hProcess, hModule, name, 300 * sizeof(char));
                if(! strcmp(pName, name))
                    pID = procs[i];
            }

        }

        CloseHandle(hProcess);
    }

    return pID;

}

int main(void){
    HMODULE psapiLib = LoadLibrary("C:\\Windows\\SysWOW64\\psapi.dll");
    if(! psapiLib) ErrorMessage("Error loading psapi.dll\n");

    DWORD pID = 0;
    pID = FindProcessID(psapiLib, "main.exe");
    if(! pID) ErrorMessage("Failed to locate main.exe program\n");
    printf("main.exe: %d\n", pID);

    // dll soon to be injected
    LPSTR dllPath = ".\\dlls\\mainDll.dll";

    // Open a handle
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
    if(! hProcess) ErrorMessage("Failed to get a handle to target process\n");


    // Allocate memory for the dll path in the target process
    LPVOID addressDll = VirtualAllocEx(hProcess, 0, strlen(dllPath) + 1, MEM_COMMIT, PAGE_READWRITE);
    if(! addressDll) ErrorMessage("Error allocating memory in target process for the dll\n");

    // Write the dll path to the target process
    WriteProcessMemory(hProcess, addressDll, (LPVOID)dllPath, strlen(dllPath) + 1, 0);

    // Create a thread in the target process to make the program load our dll
    HANDLE hLoadThread = CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"), 
                                            "LoadLibraryA"), addressDll, 0, 0);
    if(! hLoadThread) ErrorMessage("Failed to get a thread to target process\n");

    // Wait for the execution of the loader thread to finish
    WaitForSingleObject(hLoadThread, INFINITE);
    printf("Dll allocated at: %p\n", addressDll);

    // Free the memory allocaded for our dll path
    VirtualFreeEx(hProcess, addressDll, strlen(dllPath) + 1, MEM_RELEASE);

    return EXIT_SUCCESS;
}