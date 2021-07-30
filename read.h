#ifndef READ_H
#define READ_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

void verifyArgsLength(int numArgs);
void fileWasOpened(FILE *file);
void getNMvalues(FILE *input, int *n, int *m);

#endif /* READ_H */