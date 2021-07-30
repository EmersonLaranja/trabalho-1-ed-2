#include "edge.h"

struct edge
{
  Point *src;
  Point *dst;
  double wt;
};

double returnWeigth(Edge *edge) { return edge->wt; }

Edge *createEdge(Point *src, Point *dst, unsigned int tam)
{
  Edge *newEdge = (Edge *)malloc(sizeof(Edge));
  newEdge->src = src;
  newEdge->dst = dst;

  newEdge->wt = distance(src, dst, tam);

  return newEdge;
}

Edge **initArrayEdges(unsigned int n)
{
  int k = n * (n - 1) / 2;
  Edge **arrayEdges = (Edge **)malloc(sizeof(Edge *) * k);

  return arrayEdges;
}

void fillEdge(Edge **arrayEdges, unsigned int n, Point **points, unsigned int m)
{
  int k = 0;

  for (unsigned int i = 0; i < (n - 1); i++)
  {
    for (unsigned int j = i + 1; j < n; j++)
    {
      arrayEdges[k] = createEdge(points[i], points[j], m);

      k++;
    }
  }
}

void destroyEdge(Edge *edge, unsigned int tam)
{
  free(edge);
}

void printEdge(Edge *edge, unsigned int m)
{
  printf("%lf\n", edge->wt);
}

void printArrayEdges(Edge **arrayEdges, unsigned int n, unsigned int m)
{
  for (unsigned int i = 0; i < n * ((n - 1) / 2); i++)
  {
    printEdge(arrayEdges[i], m);
  }
}

void destroyArrayEdges(Edge **arrayEdges, unsigned int n, unsigned int m)
{
  for (unsigned int i = 0; i < (n * (n - 1) / 2); i++)
  {
    destroyEdge(arrayEdges[i], m);
  }
  free(arrayEdges);
}

static int compare(const void *a, const void *b)
{

  Edge *edgeA = *(Edge **)a;
  Edge *edgeB = *(Edge **)b;
  return (edgeA->wt > edgeB->wt);
}

void sortEdges(Edge **arrayEdges, unsigned int n)
{
  qsort(arrayEdges, (n * (n - 1)) / 2, sizeof(Edge *), compare);
};

Point *returnSrc(Edge *edge)
{
  return edge->src;
}

Point *returnDst(Edge *edge)
{
  return edge->dst;
}