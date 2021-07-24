#if !defined(UF_H)
#define UF_H

#include <stdlib.h>
#include <string.h>

typedef struct subset Subset;

Subset* createSubset(int qntVertices);

int find(Subset *subsets, int i);

void Union(Subset *subsets, int x, int y);

int returnParent (Subset *subsets);

void destroySubset(Subset *subset);

#endif // UF_H
