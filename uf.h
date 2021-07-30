#if !defined(UF_H)
#define UF_H

#include <stdlib.h>
#include <string.h>
#include "edge.h"

typedef struct subset Subset;

Subset **createSubset(int qntVertices);

int find(Subset **subsets, int key);

void Union(Subset **subsets, int parentSrc, int parentDst);

int returnParent(Subset *subsets);

void kruskal(Edge **result, Subset **subsetsArray, Edge **arrayEdges, int maxSizeResult, int qtdElements);

void changeParent(Subset **subsetsArray, int pos, int value);

void destroySubset(Subset **subset, int qntVertices);

#endif // UF_H
