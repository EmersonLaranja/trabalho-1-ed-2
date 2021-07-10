#if !defined(POINT_H)
#define POINT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct point Point;

Point* initPoint(Point* point, char* id, double *coordArray, unsigned int m);

void printPoint(Point* point, unsigned int m);
double distance(Point *x, Point *y, unsigned int m);

Point* destroyPoint(Point* point);

#endif // POINT_H