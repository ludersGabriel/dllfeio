#include <stdio.h>

__declspec(dllexport) int __cdecl Add(int a, int b){
    printf("Im adding %d with %d\n", a, b);
    return a + b;
}