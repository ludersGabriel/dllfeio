#include <stdio.h>
#include <stdlib.h>

__declspec(dllimport) int __cdecl Add(int a, int b);

int main(int argc, char** argv){
    printf("Result: %d\n", Add(3, 2));

    return 0;
}