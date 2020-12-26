#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD callReason, LPVOID lpReserved){
    if(callReason == DLL_PROCESS_ATTACH){
        MessageBox(0, "Hello from the injected dll", "Hello", MB_ICONINFORMATION);
    }

    if(callReason == DLL_PROCESS_DETACH){
        MessageBox(0, "mainDll.dll has been detached from the program", "goodbye", MB_ICONINFORMATION);
    }

    return TRUE;
}

