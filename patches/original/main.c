#include <stdio.h>
#include <windows.h>
#define PAGESIZE 10

void ErrorMessage(const char *message){
    fprintf(stderr, message);
    exit(EXIT_FAILURE);
}


int main(void){
    HANDLE myHandle = GetCurrentProcess();
    if(!myHandle) ErrorMessage("Error loading current process\n");    
    
    HMODULE maindllHandle = LoadLibrary("maindll.dll");
    if(!maindllHandle) ErrorMessage("Failed to load maindll.dll\n");

    unsigned char* bufferMain[PAGESIZE];
    DWORD amount = 0;
    BOOL resp = ReadProcessMemory(myHandle, maindllHandle, bufferMain, PAGESIZE, &amount);
    if(!resp) ErrorMessage("Error Reading Main buffer\n");

    for(unsigned int i = 0; i < amount; i++){
        printf("%d main: %x\n", i, bufferMain[i]);
    }

    printf("HANDLES: %p\n", maindllHandle);

    for(;;);

    return EXIT_SUCCESS;
}