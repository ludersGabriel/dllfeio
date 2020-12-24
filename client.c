#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef int (__cdecl *AddFunc)(int a, int b);
typedef BOOL (__cdecl *EnumFunc)(DWORD *lpidProcess, DWORD cb, LPDWORD lpcbNeeded);
typedef DWORD (__cdecl *GetName)(HANDLE hprocess, LPSTR name, DWORD size);

__declspec(dllimport) DWORD __cdecl GetProcessImageFileNameA(HANDLE hprocess, LPSTR name, DWORD size);

int main(int argc, char** argv){
    LPSTR fileName;
    DWORD size;
    HANDLE currentHandle = GetCurrentProcess();
    fileName = malloc(sizeof(LPSTR) * 1000);

    size = GetProcessImageFileNameA(currentHandle, fileName, 1000 * sizeof(char));
    printf("\nMy full path is: %s\n", fileName);

    CloseHandle(currentHandle);

    return 0;
}