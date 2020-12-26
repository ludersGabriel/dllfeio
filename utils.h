#ifndef UTILS_H
#define UTILS_H

void ErrorMessage(const char *message);
void** AllocaMatriz(int varSize, int lin, int col);
void FreeMatriz(void ***matriz);

#endif  