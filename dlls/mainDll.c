#include <Windows.h>
#include <stdio.h>


int sum(int a, int b){
    return (a+b);
}

__declspec(dllexport) int __stdcall Add(int a, int b){
    return sum(a,b);
}

typedef BOOL (__stdcall *GetModuleHandleExA)(DWORD flags, LPCSTR name, HMODULE *hModule);

void ErrorMessage(const char *message){
    fprintf(stderr, message);
    exit(EXIT_FAILURE);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD callReason, LPVOID lpReserved){
    if(callReason == DLL_PROCESS_ATTACH){
        HMODULE kernelLib = LoadLibrary("Kernel32.dll");
        if(! kernelLib){ 
            sum(1, 2);
            ErrorMessage("Error loading Kernel32.dll\n");
        }
        GetModuleHandleExA getmHandle = GetProcAddress(kernelLib, "GetModuleHandleExA");
        if(! getmHandle) ErrorMessage("Error loading getMHandle\n");
        
        HMODULE mHandle;
        getmHandle(GET_MODULE_HANDLE_EX_FLAG_PIN, "D:\\Dev\\Gregio\\dllfeio\\dlls\\mainDll.dll", &mHandle);
        if(! mHandle) ErrorMessage("Error getting persistent handleeeeeee\n");
        
        OutputDebugStr("Im a output string");

        MessageBox(0, "Hello from the injected dll", "Hello", MB_ICONINFORMATION);
    }

    if(callReason == DLL_PROCESS_DETACH){
        MessageBox(0, "mainDll.dll has been detached from the program", "goodbye", MB_ICONINFORMATION);
    }

    return TRUE;
}

