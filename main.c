#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define LIN 40
#define COL 400

typedef DWORD (__stdcall *EnumModules)(HANDLE hprocess, HMODULE *moduleHandles, DWORD cb, LPDWORD lpcNeeded);
typedef DWORD (__stdcall *GetModuleName)(HANDLE hprocess, HMODULE hmodule, LPSTR name, DWORD size);

void InitializeMatrix(char*** matrix){
    for(int i = 0; i < LIN; i++)
        strcpy((*matrix)[i], "");
}

char** GetModules( HANDLE pHandle)
{
    HMODULE hMods[1024];
    DWORD cbNeeded;
    unsigned int i;

    if (NULL == pHandle) ErrorMessage("Null process handle\n");

    // Loads the lib
    HMODULE psapiLib = LoadLibrary("C:\\Windows\\SysWOW64\\psapi.dll");
    if(! psapiLib) ErrorMessage("Error loading psapi.dll\n");

    // Get the functions we need from the lib
    EnumModules getModules = (EnumModules)GetProcAddress(psapiLib, "EnumProcessModules");
    GetModuleName getModuleName = (GetModuleName)GetProcAddress(psapiLib, "GetModuleFileNameExA");
    if(!getModules) ErrorMessage("Error finding EnumProcessModules from psapi.dll\n");
    if(!getModuleName) ErrorMessage("Error finding GetModuleFileNameExA from psapi.dll\n");


   // Get a list of all the modules in this process.

    char** names = (char**)AllocaMatriz(sizeof(char), LIN, COL);
    InitializeMatrix(&names);

    if( getModules(pHandle, hMods, sizeof(hMods), &cbNeeded))
    {
        for ( i = 0; i < (cbNeeded / sizeof(HMODULE)); i++ )
        {
            LPSTR szModName;
            szModName = malloc(1024 * sizeof(LPSTR));

            // Get the full path to the module's file.

            // change GetModuleFileNameExA with getModuleName to see the error
            if ( getModuleName( pHandle, hMods[i], szModName, 1024 * sizeof(char))){
                // Print the module name and handle value.
                strcpy(names[i], szModName);
            }

            free(szModName);
        }
    }

    return names;
}

char** GetNonSystemModules(char **modules){
    char** nonSystem = (char **) AllocaMatriz(sizeof(char), LIN, COL);
    InitializeMatrix(&nonSystem);

    for(int i = 0; i < LIN; i++){
        if(strlen(modules[i])){
            if(! strstr(modules[i], "C:\\Windows") && !strstr(modules[i], "main.exe"))
                strcpy(nonSystem[i], modules[i]);
        }
    }

    return nonSystem;
}

void FreeM(const char *mName){
    HMODULE mHandle = GetModuleHandleA(mName);
    FreeLibrary(mHandle);
    char message[200];
    sprintf(message, "%s tomou unloadload do programa", mName);
    MessageBox(0, message, "dLoad", MB_ICONINFORMATION);
}


int main( void )
{
    HANDLE myHandle = GetCurrentProcess();
    char **modules = NULL;
    char **nonSystem = NULL;
    char input;

    for(; ;){
        modules = GetModules(myHandle);
        nonSystem = GetNonSystemModules(modules);
        if(modules){
            printf("\nThese are all my modules\n");
            for(int i = 0; i < LIN; i++)
                if(strlen(modules[i])) printf("\t%s\n", modules[i]);
        }

        if(nonSystem){
            printf("\nThese are all my nonSystem modules\n");
            for(int i = 0; i < LIN; i++){
                if(strlen(nonSystem[i])){ 
                    printf("\t%s\n", nonSystem[i]);
                    FreeM(nonSystem[i]);
                }
            }
        }

        printf("\n");
        FreeMatriz((void***) &modules);
        FreeMatriz((void ***) &nonSystem);
        Sleep(1000 * 2);
        system("cls");
        
    }
    CloseHandle(myHandle);

    return 0;
}