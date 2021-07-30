#include "uf.h"
#include "edge.h"
struct subset
{
    int parent;
    int rank;
};

Subset **createSubset(int qntVertices)
{
    Subset **new = (Subset **)malloc(qntVertices * sizeof(Subset *));

    for (int v = 0; v < qntVertices; ++v)
    {
        new[v] = (Subset *)malloc(sizeof(Subset));
        new[v]->parent = v;
        new[v]->rank = 0;
    }
    return new;
}

int find(Subset **subsets, int key)
{
    if (subsets[key]->parent != key)
        subsets[key]->parent = find(subsets, subsets[key]->parent);

    return subsets[key]->parent;
}

void Union(Subset **subsets, int parentSrc, int parentDst)
{
    int rootSrc = find(subsets, parentSrc);
    int rootDst = find(subsets, parentDst);

    if (subsets[rootSrc]->rank < subsets[rootDst]->rank)
        subsets[rootSrc]->parent = rootDst;
    else if (subsets[rootSrc]->rank > subsets[rootDst]->rank)
        subsets[rootDst]->parent = rootSrc;

    else
    {
        subsets[rootDst]->parent = rootSrc;
        subsets[rootSrc]->rank++;
    }
}

int returnParent(Subset *subsets)
{
    return subsets->parent;
}

void changeParent(Subset **subsetsArray, int pos, int value)
{
    subsetsArray[pos]->parent = value;
}

void kruskal(Edge **result, Subset **subsetsArray, Edge **arrayEdges, int maxSizeResult, int qtdElements)
{
    int qtdItemsResult = 0, counter = 0;
    while (qtdItemsResult < maxSizeResult) //qnt item menor que a qnt de arestas necessárias
    {
        Edge *nextEdge = arrayEdges[counter];

        int parentSrc = find(subsetsArray, returnIdNum(returnSrc(nextEdge)));
        int parentDst = find(subsetsArray, returnIdNum(returnDst(nextEdge)));

        if (parentSrc != parentDst)
        {
            result[qtdItemsResult] = nextEdge;
            qtdItemsResult++;
            Union(subsetsArray, parentSrc, parentDst);
        }

        counter++;
    }

    //aqui mudamos o valor do pai para o valor do pai raiz, pensando que podemos ter vários filhos
    int y;

    for (int j = 0; j < qtdElements; j++)
    {
        y = j;
        if (returnParent(subsetsArray[j]) != j)
        {
            while (returnParent(subsetsArray[y]) != y)
            {
                y = returnParent(subsetsArray[y]);
                for (int i = 0; i < qtdElements; i++)
                {
                    if (returnParent(subsetsArray[i]) == j)
                    {
                        changeParent(subsetsArray, i, y);
                    }
                }
            }
        }
    }
};

void destroySubset(Subset **subset, int qntVertices)
{
    for (int i = 0; i < qntVertices; i++)
    {
        free(subset[i]);
    }

    free(subset);
}