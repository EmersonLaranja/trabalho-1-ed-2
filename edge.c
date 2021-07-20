#include "edge.h"

struct node
{
  int parent;
  int rank;
};

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
  // for (int i = 0; i < tam; i++)
  // {
  //   free(edge->src); //!REVIEW: temos que definir se vamos excluir os pontos ao excluir um edge. Até então não vejo problema
  //   free(edge->dst); //!REVIEW: temos que definir se vamos excluir os pontos ao excluir um edge. Até então não vejo problema
  // }
  free(edge);
}

void printEdge(Edge *edge, unsigned int m)
{
  printPoint(edge->src, m);
  printPoint(edge->dst, m);
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

  Edge *edgeA = (Edge *)a;
  Edge *edgeB = (Edge *)b;
  printEdge(edgeA, 10);
  printEdge(edgeB, 10);

  return (edgeB->wt - edgeA->wt);
}

void sortEdges(Edge **arrayEdges, unsigned int n)
{
  qsort(arrayEdges, (n * (n - 1)) / 2, sizeof(Edge), compare);
};
