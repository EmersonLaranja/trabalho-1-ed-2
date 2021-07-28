#include "UF.h"
// A structure to represent a subset for union-find
struct subset
{
    int parent;
    int rank;
};

Subset **createSubset(int qntVertices)
{
    Subset **newSubset = (Subset **)malloc(qntVertices * sizeof(Subset *));

    for (int v = 0; v < qntVertices; ++v)
    {
        newSubset[v] = (Subset *)malloc(sizeof(Subset));
        newSubset[v]->parent = v;
        newSubset[v]->rank = 0;
    }
    return newSubset;
}

// A utility function to find set of an element i
// (uses path compression technique)
int find(Subset **subsets, int i)
{
    // find root and make root as parent of i
    // (path compression)
    if (subsets[i]->parent != i)
        subsets[i]->parent = find(subsets, subsets[i]->parent);

    return subsets[i]->parent;
}

// A function that does union of two sets of x and y
// (uses union by rank)
void Union(Subset **subsets, int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // Attach smaller rank tree under root of high
    // rank tree (Union by Rank)
    if (subsets[xroot]->rank < subsets[yroot]->rank)
        subsets[xroot]->parent = yroot;
    else if (subsets[xroot]->rank > subsets[yroot]->rank)
        subsets[yroot]->parent = xroot;

    // If ranks are same, then make one as root and
    // increment its rank by one
    else
    {
        subsets[yroot]->parent = xroot;
        subsets[xroot]->rank++;
    }
}

int returnParent(Subset *subsets)
{
    return subsets->parent;
}

// Subset returnSubset(Subset subsetArray[], int id){
//     return subsetArray[id];
// }

static int counterGroupItem(int i, int qtd, Subset **subsets)
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

static int verifyParent(int parent, int *parentArray, int k)
{
    for (unsigned int i = 0; i < k; i++)
    {
        if (parentArray[i] == parent)
        {
            return 1;
        }
        else if (parentArray[i] == -1)
        {
            return 0;
        }
    }

    return 0;
}

void printSameFather(FILE *file, Subset **subsets, Point **points, int qtd, int k)
{

    int parentArray[k];
    initParentArray(k, parentArray);
    int count = 0;
    int flag = 0;
    for (int i = 0; i < qtd; i++)
    {
        if (verifyParent(returnParent(subsets[i]), parentArray, k))
        {
            continue;
        }
        count = counterGroupItem(i, qtd, subsets);
        fprintf(file, "%s", returnId(points[i]));
        count--;

        if (count != 0)
        {
            fprintf(file, ",");
        }

        for (int j = i + 1; j < qtd; j++)
        {

            if (subsets[j]->parent == subsets[i]->parent)
            {
                fprintf(file, "%s", returnId(points[j]));
                count--;
                if (count != 0)
                {
                    fprintf(file, ",");
                }
            }
        }
        parentArray[flag] = subsets[i]->parent;
        flag++;
        fprintf(file, "\n");
    }
}

void destroySubset(Subset **subset, int qntVertices)
{
    for (int i = 0; i < qntVertices; i++)
    {
        free(subset[i]);
    }

    free(subset);
}