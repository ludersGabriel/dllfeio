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

    HMODULE fakeHandle = LoadLibrary("fake.dll");
    if(!fakeHandle) ErrorMessage("Failed to load fake.dll\n");


    DWORD fakeAmount, mainAmount;
    fakeAmount = mainAmount = 0;

    char* bufferMain[PAGESIZE];
    BOOL resp = ReadProcessMemory(myHandle, maindllHandle, bufferMain, PAGESIZE, &mainAmount);
    if(!resp) ErrorMessage("Error Reading Main buffer\n");

    char *bufferFake[PAGESIZE];
    resp = ReadProcessMemory(myHandle, fakeHandle, bufferFake, PAGESIZE, &fakeAmount);
    if(!resp) ErrorMessage("Error Reading fake buffer\n");


    for(unsigned int i = 0; i < mainAmount && i < fakeAmount; i++){
        printf("main: %x\nfake: %x\n\n", bufferMain[i], bufferFake[i]);
    }

    printf("HANDLES: %p, %p\n", maindllHandle, fakeHandle);

    for(;;);

    return EXIT_SUCCESS;
}