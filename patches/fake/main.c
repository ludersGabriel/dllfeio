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
    
    HMODULE fakeHandle = LoadLibrary("fake.dll");
    if(!fakeHandle) ErrorMessage("Failed to load fake.dll\n");

    DWORD amount;
    unsigned char *bufferFake[PAGESIZE];
    BOOL resp = ReadProcessMemory(myHandle, fakeHandle, bufferFake, PAGESIZE, &amount);
    if(!resp) ErrorMessage("Error Reading fake buffer\n");


    for(unsigned int i = 0; i < amount; i++){
        printf("%d fake: %x\n", i, bufferFake[i]);
    }

    printf("HANDLES: %p\n", fakeHandle);

    for(;;);

    return EXIT_SUCCESS;
}