#if !defined(UF_H)
#define UF_H

typedef struct subset Subset;

Subset* createSubset(int qntVertices);

int find(struct subset subsets[], char* i);


void Union(struct subset subsets[], int x, int y);

#endif // UF_H
