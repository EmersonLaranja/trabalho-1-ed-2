#if !defined(EDGE_H)
#define EDGE_H

typedef struct node Node;
typedef struct edge Edge;
#include "point.h"

Edge *createEdge(Point *src, Point *dst, unsigned int tam);

Edge **initArrayEdges(unsigned int n);

void fillEdge(Edge **arrayEdges, unsigned int n, Point **points, unsigned int m);

void destroyEdge(Edge *edge, unsigned int tam);

void printEdge(Edge *edge, unsigned int m);

void printArrayEdges(Edge **arrayEdges, unsigned int n, unsigned int m);

double returnWeigth(Edge *edge);

void destroyArrayEdges(Edge **arrayEdges, unsigned int n, unsigned int m);

void sortEdges(Edge **arrayEdges, unsigned int n);

#endif // EDGE_H
