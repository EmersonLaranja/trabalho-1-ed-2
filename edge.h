#if !defined(EDGE_H)
#define EDGE_H

#include "point.h"

typedef struct node Node;
typedef struct edge Edge;

Edge *createEdge(Point *src, Point *dst, unsigned int tam);

void destroyEdge(Edge *edge, unsigned int tam);

void print_edge(Edge *edge);

#endif // EDGE_H
