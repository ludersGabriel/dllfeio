#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
// #include "add.h"

typedef int (__cdecl *AddFunc)(int a, int b);
typedef BOOL (__cdecl *EnumFunc)(DWORD *lpidProcess, DWORD cb, LPDWORD lpcbNeeded);
typedef DWORD (__cdecl *GetName)(HANDLE hprocess, LPSTR name, DWORD size);
typedef DWORD (__cdecl *GetModules)(HANDLE hprocess, HMODULE *moduleHandles, DWORD cb, LPDWORD lpcNeeded);
typedef DWORD (__cdecl *GetModuleName)(HANDLE hprocess, HMODULE hmodule, LPSTR name, DWORD size);


int main(int argc, char** argv){
    HMODULE psapiLib;
    AddFunc Add;
    GetName getName;
    GetModules getModules;
    GetModuleName getModuleName;

    // tries to load the dll into the process' address space
    if(!(psapiLib = LoadLibrary(TEXT("C:\\Windows\\System32\\psapi.dll")))){
        fprintf(stderr, "Error loading \"psapi.dll\"\n");
        return EXIT_FAILURE;
    }


    if(!(getName = (GetName)GetProcAddress(psapiLib, "GetProcessImageFileNameA"))){
        fprintf(stderr, "Error locating \"GetModuleFileNameA\" function.\n");
        return EXIT_FAILURE;
    }

    if(!(getModules = (GetModules)GetProcAddress(psapiLib, "EnumProcessModules"))){
        fprintf(stderr, "Error locating EnumProcessModules from psapi.dll");
        return EXIT_FAILURE;
    }

    if(!(getModuleName = (GetModuleName)GetProcAddress(psapiLib, "GetModuleFileNameExA"))){
        fprintf(stderr, "Error locating GetModuleFileNameExA from psapi.dll");
        return EXIT_FAILURE;
    }

    printf("\nPsapi.dll is loaded at address %p\n", psapiLib);
    printf("GetModuleFileNameA Function is located at address %p\n", getName);
    printf("EnumProcessModules function is located at address %p\n", getModules);
    printf("GetModuleFileNameExA function is located at address %p\n", getModuleName);

    HANDLE currentHandle = GetCurrentProcess();
    LPSTR fileName;
    DWORD size;
    fileName = malloc(1024*sizeof(LPSTR));

    if( ! (size = getName(currentHandle, fileName, 1024 * sizeof(char)))){
        fprintf(stderr, "Error running GetName function.\n");
        return EXIT_FAILURE;
    }

    printf("My full path is: %s\n", fileName);

    // Unload DLL
    FreeLibrary(psapiLib);
    CloseHandle(currentHandle);

    return EXIT_SUCCESS;
}