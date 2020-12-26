#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void ErrorMessage(const char *message){
    fprintf(stderr, message);
    exit(EXIT_FAILURE);
}

void** AllocaMatriz(int varSize, int lin, int col){
    void **mat;

    mat = malloc(lin * sizeof(void *));
    if(! mat) ErrorMessage("Erro mallocando memoria para o vetor de linhas\n");
    mat[0] = malloc(lin * col * varSize);
    if(! mat[0]) ErrorMessage("Erro mallocando memoria para os elementos");

    for(int i = 1; i < lin; i++) mat[i] = mat[0] + col * i * varSize;

    return mat;
}

void FreeMatriz(void ***matriz){
    free((*matriz)[0]);
    (*matriz)[0] = NULL;
    free(*matriz);
    *matriz = NULL;
}



