#include <stdio.h>
#include "add.h"

int ADDCALL Add(int a, int b){
    printf("Im adding %d with %d\n", a, b);
    return a + b;
}