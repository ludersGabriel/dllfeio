#include <windows.h>
#include <stdio.h>

void mess(void){
    MessageBoxA(0, "im the ousider box", "box?", MB_ICONINFORMATION);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD callReason, LPVOID lpReserved){
    if(callReason == DLL_PROCESS_ATTACH){
        printf("im the attach function of the dll\n");        
    }

    if(callReason == DLL_PROCESS_DETACH){
        printf("i've been detached\n");
    }

    return TRUE;
}