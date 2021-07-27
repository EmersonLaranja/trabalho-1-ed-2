#if !defined(UF_H)
#define UF_H

#include <stdlib.h>
#include <string.h>
#include "point.h"

typedef struct subset Subset;

Subset **createSubset(int qntVertices);

int find(Subset **subsets, int i);

void Union(Subset **subsets, int x, int y);

int returnParent(Subset *subsets);

void printSameFather(FILE *file, Subset **subsets, Point **points, int qtd);

void destroySubset(Subset **subset, int qntVertices);

#endif // UF_H
