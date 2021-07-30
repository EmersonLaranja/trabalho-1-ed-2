
#include "point.h"
#include <math.h>

struct point
{
  char *id;
  unsigned int idNum;
  double *coordArray;
};

void initPointArray(Point **arrayPoints, FILE *file, int length)
{
  char *id;
  char *coord;
  char *buffer = NULL;
  size_t bufsize = 0;
  ssize_t qtdChar = 0;
  const char comma[2] = ","; //onde havera o split exigido pelo strtok;
  double coordArray[length];
  unsigned int posi;
  unsigned int countPoints = 0;

  qtdChar = getline(&buffer, &bufsize, file);
  while (qtdChar >= 0)
  {
    posi = 0;

    //Le o id;
    id = strtok(buffer, comma);

    //Le primeira coordenada;
    coord = strtok(NULL, comma);
    while (coord != NULL)
    {
      coordArray[posi] = atof(coord); //armazena a coord no vetor;
      posi++;                         // incrementa posição do vetor;
      coord = strtok(NULL, comma);    //Lê a prox coord;
    }

    //Cria a Struct do Ponto;
    Point *point = initPoint(point, id, coordArray, length);
    arrayPoints[countPoints] = point;
    countPoints++;

    qtdChar = getline(&buffer, &bufsize, file);
  }
  free(buffer);
};

Point *initPoint(Point *point, char *id, double *coordArray, unsigned int m)
{
  Point *newPoint = (Point *)malloc(sizeof(Point));
  newPoint->id = strdup(id);
  newPoint->coordArray = (double *)malloc(sizeof(double) * m);
  for (unsigned int i = 0; i < m; i++)
  {
    newPoint->coordArray[i] = coordArray[i];
  }
  newPoint->idNum = -1;
  return newPoint;
}

void fillIdNum(Point **pointArray, int length)
{
  for (int i = 0; i < length; i++)
  {
    pointArray[i]->idNum = i;
  }
}

void printPoint(Point *point /*, unsigned int m*/)
{

  printf("%s ", point->id);
}

unsigned int returnIdNum(Point *point)
{
  return point->idNum;
}

char *returnId(Point *point)
{
  return point->id;
}

void destroyPointsArray(Point **pointsArray, int length)
{
  for (unsigned int i = 0; i < length; i++)
  {
    destroyPoint(pointsArray[i]);
  }
}

void destroyPoint(Point *point)
{
  free(point->coordArray);
  free(point->id);

  free(point);
}

double distance(Point *x, Point *y, unsigned int m)
{
  double sum = 0.0;
  for (unsigned int i = 0; i < m; i++)
  {
    sum += (y->coordArray[i] - x->coordArray[i]) * (y->coordArray[i] - x->coordArray[i]);
  }

  return sqrt(sum);
}

int comparePoints(const void *a, const void *b)
{
  Point *x = *(Point **)a;
  Point *y = *(Point **)b;

  return strcmp(returnId(x), returnId(y));
}