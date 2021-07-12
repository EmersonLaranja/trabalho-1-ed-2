#if !defined(MATRIX_H)
#define MATRIX_H
#include "point.h"

void fillMatrix(unsigned int n, double **pointsMatrix, Point **points, unsigned int m);
void printMatrix(FILE *log, unsigned int n, double **pointsMatrix, unsigned int m);
double **initMatrix(int nlines, int ncolumns);
double **destroyMatrix(double **matrix, int nlines, int ncolumns);
#endif // MATRIX_H
