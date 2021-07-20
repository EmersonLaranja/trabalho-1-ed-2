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

Edge *createEdge(Point *src, Point *dst, unsigned int tam)
{
  Edge *newEdge = (Edge *)malloc(sizeof(Edge));
  newEdge->src = src;
  newEdge->dst = dst;

  newEdge->wt = distance(src, dst, tam);

  printEdge(newEdge, tam);
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
