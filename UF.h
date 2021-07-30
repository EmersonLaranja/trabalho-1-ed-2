#if !defined(UF_H)
#define UF_H

#include <stdlib.h>
#include <string.h>
#include "edge.h"

typedef struct subset Subset;

Subset **createSubset(int qntVertices);

int find(Subset **subsets, int key);

void Union(Subset **subsets, int x, int y);

int returnParent(Subset *subsets);

void destroySubset(Subset **subset, int qntVertices);

int counterGroupItem(int i, int qtd, Subset **subsets);

void kruskal(Edge **result, Subset **subsetsArray, Edge **arrayEdges, int maxSizeResult);

void changeParent(Subset **subsetsArray, int pos, int value);

#endif // UF_H
