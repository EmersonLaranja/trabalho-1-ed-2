#include <time.h>
#include "read.h"
#include "edge.h"
#include "UF.h"
#include "list.h"

int main(int argc, char const *argv[])
{
  clock_t start, stop; //variaveis para medição do tempo
  start = clock();

  verifyArgsLength(argc); //verifica se foram passados todos os argumentos

  unsigned int k = atoi(argv[2]); //quantidade de grupos desejados

  // Verifica abertura de arquivos;
  FILE *inputFile = fopen(argv[1], "r");
  fileWasOpened(inputFile);

  FILE *logFile = fopen(argv[3], "w");
  fileWasOpened(logFile);

  unsigned int n = 0; //quantidade de elementos;
  unsigned int m = 0; //quantidade de coordenadas;

  getNMvalues(inputFile, &n, &m);
  // //Reinicia leitura do arquivo de entrada
  rewind(inputFile);

  Point *points[n];
  initPointArray(points, inputFile, m);
  //ordenando pontos lexicográficamente
  qsort(points, n, sizeof(Point *), comparePoints);

  fillIdNum(points, n); //id numerico usado para comparação no union/find

  Edge **arrayEdges = initArrayEdges(n); //vetor com as arestas que unem os pontos

  fillEdge(arrayEdges, n, points, m);

  //ordenando pela distancia entre os pontos src e dst
  sortEdges(arrayEdges, n);

  Subset **subsetsArray = createSubset(n);

  int counter = 0, qtdItemsResult = 0, maxSizeResult = n - k;
  Edge *result[maxSizeResult]; // os Edges restantes para nossa MST

  // // kruskal(subsetsArray, arrayEdges, qtdItemsResult, maxSizeResult);

  while (qtdItemsResult < maxSizeResult) //qnt item menor que a qnt de arestas necessárias
  {
    Edge *nextEdge = arrayEdges[counter];

    int x = find(subsetsArray, returnIdNum(returnSrc(nextEdge)));
    int y = find(subsetsArray, returnIdNum(returnDst(nextEdge)));

    if (x != y)
    {
      result[qtdItemsResult] = nextEdge;
      qtdItemsResult++;
      Union(subsetsArray, x, y);
    }

    counter++;
  }

  // Vetor de pontos com k listas

  FILE *test = fopen("printpoints.txt", "w");
  fileWasOpened(test);
  for (int i = 0; i < n; i++)
  {
    fprintf(test, "Ponto:%s Pai: %s \n", returnId(points[i]), returnId(points[returnParent(subsetsArray[i])]));
  }
  fclose(test);

  int y;
  for (int j = 0; j < n; j++)
  {
    y = j;
    if (returnParent(subsetsArray[j]) != j)
    {
      while (returnParent(subsetsArray[y]) != y)
      {
        y = returnParent(subsetsArray[y]);
        for (int i = 0; i < n; i++)
        {
          if (returnParent(subsetsArray[i]) == j)
          {
            changeParent(subsetsArray, i, y);
          }
        }
      }
    }
  }

  List *groupsList[k];
  int lengGroup = 0, posi;
  for (int i = 0; i < k; i++)
  {
    groupsList[i] = initList();
  }
  int c;

  for (int i = 0, posi = 0; i < n; i++)
  {
    c = 0;
    for (int j = 0; j < n; j++)
    {
      if (returnParent(subsetsArray[j]) == i)
      {
        insertList(groupsList[posi], points[j]);

        c = 1;
      }
    }
    if (c)
    {
      posi++;
    }
  }

  /*
  Na hora de preencher um grupo eu busco o máximo pai de j e comparo com i, se forem iguais eu coloco o elemento j no grupo
  pra achar o máximo pai de j, eu faço um while até que uma dada posicao k do vetor seja igual ao pai
  */

  qsort(groupsList, k, sizeof(List *), compareLists);

  // Ordenar groupList

  printGroupList(groupsList, k, logFile);

  // // --------------------------DESTRUIÇÕES-----------------------

  // //destruindo grupos de listas
  destroyGroupList(groupsList, k);

  destroyArrayEdges(arrayEdges, n, m);
  // //destruindo o vetor de pontos
  destroyPointsArray(points, n);

  destroySubset(subsetsArray, n);

  fclose(inputFile);

  fclose(logFile);
  stop = clock();

  double time_taken = ((double)stop - start) / CLOCKS_PER_SEC;

  //Verificando o tempo de execução
  printf("\nTEMPO %.4f\n", time_taken);
  return 0;
}
