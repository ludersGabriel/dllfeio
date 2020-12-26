#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

typedef DWORD (__stdcall *EnumModules)(HANDLE hprocess, HMODULE *moduleHandles, DWORD cb, LPDWORD lpcNeeded);
typedef DWORD (__stdcall *GetModuleName)(HANDLE hprocess, HMODULE hmodule, LPSTR name, DWORD size);

void ErrorMessage(const char *message){
    fprintf(stderr, message);
    exit(EXIT_FAILURE);
}

int PrintModules( HANDLE pHandle )
{
    HMODULE hMods[1024];
    DWORD cbNeeded;
    unsigned int i;

    if (NULL == pHandle)
        return EXIT_FAILURE;

    // Loads the lib
    HMODULE psapiLib = LoadLibrary("C:\\Windows\\SysWOW64\\psapi.dll");
    if(! psapiLib) ErrorMessage("Error loading psapi.dll\n");

    // Get the functions we need from the lib
    EnumModules getModules = (EnumModules)GetProcAddress(psapiLib, "EnumProcessModules");
    GetModuleName getModuleName = (GetModuleName)GetProcAddress(psapiLib, "GetModuleFileNameExA");
    if(!getModules) ErrorMessage("Error finding EnumProcessModules from psapi.dll\n");
    if(!getModuleName) ErrorMessage("Error finding GetModuleFileNameExA from psapi.dll\n");


   // Get a list of all the modules in this process.

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
                printf(("\t%s (0x%08X)\n"), szModName, hMods[i] );
                
            }

            free(szModName);
        }
    }

    return 0;
}

int main( void )
{
    HANDLE myHandle = GetCurrentProcess();
    for(;;){
        printf("These are all my modules\n");
        PrintModules(myHandle);
        printf("\n");

        Sleep(1000 * 2);
    }
    CloseHandle(myHandle);

    return 0;
}