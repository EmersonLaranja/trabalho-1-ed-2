#if !defined(POINT_H)
#define POINT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct point Point;

void initPointArray(Point **pointsArray, FILE *file, int length);

Point *initPoint(Point *point, char *id, double *coordArray, unsigned int qtdCoord);

void fillIdNum(Point **pointArray, int length);

void printPoint(Point *point);

double distance(Point *x, Point *y, unsigned int qtdCoord);

unsigned int returnIdNum(Point *point);

char *returnId(Point *point);

void sortPoints(Point **pointsArray, int qtdPoints);

void destroyPoint(Point *point);

void destroyPointsArray(Point **pointsArray, int length);

int comparePoints(const void *a, const void *b);

#endif // POINT_H