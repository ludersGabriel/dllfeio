#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
// #include "add.h"

typedef int (__cdecl *AddFunc)(int a, int b);
typedef BOOL (__cdecl *EnumFunc)(DWORD *lpidProcess, DWORD cb, LPDWORD lpcbNeeded);
typedef DWORD (__cdecl *GetName)(HANDLE hprocess, LPSTR name, DWORD size);


int main(int argc, char** argv){
    HMODULE hAddLib;
    AddFunc Add;
    GetName getName;

    HANDLE currentHandle = GetCurrentProcess();

    // tries to load the dll into the process' address space
    if(!(hAddLib = LoadLibrary(TEXT("C:\\Windows\\System32\\psapi.dll")))){
        fprintf(stderr, "Error loading \"psapi.dll\"\n");
        return EXIT_FAILURE;
    }

    printf("Library is loaded at address %p\n", hAddLib);

    if(!(getName = (GetName)GetProcAddress(hAddLib, "GetProcessImageFileNameA"))){
        fprintf(stderr, "Error locating \"GetModuleFileNameA\" function.\n");
        return EXIT_FAILURE;
    }

    printf("GetModuleFileNameA Function is located at address %p\n", getName);
 
    LPSTR fileName;
    DWORD size;

    fileName = malloc(sizeof(LPSTR) * 1000);

    if( ! (size = getName(currentHandle, fileName, 1000 * sizeof(char)))){
        fprintf(stderr, "Error running GetName function.\n");
        return EXIT_FAILURE;
    }

    printf("\nMy full path is: %s\n", fileName);

    // Unload DLL
    FreeLibrary(hAddLib);
    CloseHandle(currentHandle);

    return 0;
}