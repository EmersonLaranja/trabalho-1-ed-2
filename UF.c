#include "UF.h"
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

int find(Subset **subsets, int i)
{
    if (subsets[i]->parent != i)
        subsets[i]->parent = find(subsets, subsets[i]->parent);

    return subsets[i]->parent;
}

void Union(Subset **subsets, int x, int y)
{
    int rootSrc = find(subsets, x);
    int rootDst = find(subsets, y);

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

int counterGroupItem(int i, int qtd, Subset **subsets)
{
    int counter = 0;
    for (int k = 0; k < qtd; k++)
    {
        if (subsets[i]->parent == subsets[k]->parent)
            counter++;
    }
    return counter;
}

static void initParentArray(int k, int *parentArray)
{
    for (unsigned int i = 0; i < k; i++)
    {
        parentArray[i] = -1;
    }
}

static int verifyParent(int position, Subset **subsets, int parent)
{
    for (int i = position - 1; i >= 0; i--)
    {
        if (subsets[i]->parent == parent)
        {
            return 1;
        }
    }

    return 0;
}

void destroySubset(Subset **subset, int qntVertices)
{
    for (int i = 0; i < qntVertices; i++)
    {
        free(subset[i]);
    }

    free(subset);
}

void changeParent(Subset **subsetsArray, int pos, int value)
{
    subsetsArray[pos]->parent = value;
}

void kruskal(Edge **result, Subset **subsetsArray, Edge **arrayEdges, int maxSizeResult)
{
    int qtdItemsResult = 0, counter = 0;
    while (qtdItemsResult < maxSizeResult) //qnt item menor que a qnt de arestas necessárias
    {
        Edge *nextEdge = arrayEdges[counter];

        int x = find(subsetsArray, returnIdNum(returnSrc(nextEdge)));
        int y = find(subsetsArray, returnIdNum(returnDst(nextEdge)));

        if (x != y)
        {
            result[qtdItemsResult] = nextEdge;
            qtdItemsResult++;
            Union(subsetsArray, x, y);
        }

        counter++;
    }
};
