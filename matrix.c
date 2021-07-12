#include "matrix.h"

void fillMatrix(unsigned int n, double **pointsMatrix, Point **points, unsigned int m)
{

  for (unsigned int i = 0; i < (n - 1); i++)
  {
    for (unsigned int j = i + 1; j < n; j++)
    {
      pointsMatrix[j][i] = distance(points[i], points[j], m);
    }
  }
}

void printMatrix(FILE *log, unsigned int n, double **pointsMatrix, unsigned int m)
{
  for (unsigned int i = 0; i < n; i++)
  {
    for (unsigned int j = 0; j < i; j++)
    {
      fprintf(log, "%.2f ", pointsMatrix[i][j]);
    }
    fprintf(log, "\n");
  }
}

double **initMatrix(int nlines, int ncolumns)
{

  double **m = (double **)malloc(sizeof(double *) * nlines);
  for (int i = 0; i < nlines; i++)
    m[i] = (double *)malloc(ncolumns * sizeof(double));
  return m;
}

double **destroyMatrix(double **matrix, int nlines, int ncolumns)
{

  for (int i = 0; i < nlines; i++)
    free(matrix[i]);
  free(matrix);
}
