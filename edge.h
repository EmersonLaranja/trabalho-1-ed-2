#if !defined(EDGE_H)
#define EDGE_H

typedef struct node Node;
typedef struct edge Edge;
#include "point.h"

Edge *createEdge(Point *src, Point *dst, unsigned int tam);

void destroyEdge(Edge *edge, unsigned int tam);

void printEdge(Edge *edge, unsigned int m);

#endif // EDGE_H
