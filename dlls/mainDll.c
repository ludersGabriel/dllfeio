#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD callReason, LPVOID lpReserved){
    if(callReason == DLL_PROCESS_ATTACH){
        MessageBox(0, "Hello from the injected dll", "Hello", MB_ICONINFORMATION);
    }

    return TRUE;
}