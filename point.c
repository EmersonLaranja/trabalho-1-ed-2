
#include "point.h"
#include <math.h>

struct point{
    char* id;
    unsigned int idNum;
    double *coordArray;
};

Point* initPoint(Point* point, char* id, double *coordArray, unsigned int m, unsigned int countPoints){
    Point *newPoint = (Point*)malloc(sizeof(Point));
    newPoint->id=strdup(id);
    newPoint->coordArray = (double*)malloc(sizeof(double)*m);
    for (unsigned int i = 0; i < m;i++ )
    {
      newPoint->coordArray[i] = coordArray[i];
    }
    newPoint->idNum = countPoints;
    return newPoint;
}

void printPoint(Point* point, unsigned int m){
    
      printf("%s ",point->id);

    for  (unsigned int i = 0; i < m; i++)
    {
      printf("%.15lf ", point->coordArray[i]);
    }
printf("\n");
}

unsigned int returnIdNum(Point* point){
  return point->idNum;
}


Point* destroyPoint(Point* point){
  free(point->coordArray);
  free(point->id);


  free(point);
}

double distance(Point *x, Point *y, unsigned int m){
  double sum=0.0;
  for (unsigned int i = 0; i < m; i++)
  {
   sum+= (y->coordArray[i]-x->coordArray[i])* (y->coordArray[i]-x->coordArray[i]);
  }
  
  return sqrt(sum);
  }