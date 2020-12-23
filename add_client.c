#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
// #include "add.h"


typedef int (__cdecl *AddFunc)(int a, int b);

int main(int argc, char** argv){

    HMODULE hAddLib;
    AddFunc Add;
    
    // tries to load the dll into the process' address space
    if(!(hAddLib = LoadLibrary(TEXT("add_basic.dll")))){
        fprintf(stderr, "Error loading \"add_basic.dll\"\n");
        return EXIT_FAILURE;
    }

    printf("Library is loaded at address %p\n", hAddLib);

    if(!(Add = (AddFunc)GetProcAddress(hAddLib, "Add"))){
        fprintf(stderr, "Error locating \"Add\" function.\n");
        return EXIT_FAILURE;
    }

    printf("Add Function is located at address %p\n", Add);

    printf("Result: %d\n", Add(3, 2));

    // Unload DLL
    FreeLibrary(hAddLib);

    return 0;
}