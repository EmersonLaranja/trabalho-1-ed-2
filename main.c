
#include <stdbool.h>
#include "matrix.h"
#include <time.h>
#include "edge.h"
#include "UF.h"

int comparePoints(const void *a, const void *b);

int main(int argc, char const *argv[])
{
  clock_t start, stop; //variaveis para medição do tempo
  char *buffer = NULL;
  size_t bufsize = 0;
  ssize_t qtdChar = 0;
  const char comma[2] = ","; //onde havera o split;

  unsigned int k;

  //mensagens de erro

  if (argc < 4)
  {
    printf("ERRO: Quantidade de argumentos inválidos\n");
    exit(1);
  }

  if (argc <= 1)
  {
    printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
    exit(1);
  }

  //Transforma o K (char) da leitura em unisgned int;
  k = atoi(argv[2]);

  // Verifica abertura de arquivos;
  FILE *inputFile = fopen(argv[1], "r");

  if (inputFile == NULL)
  {
    printf("ERRO: falha na abertura do arquivo de entrada\n");
    exit(1);
  }

  FILE *logFile = fopen(argv[3], "w");

  if (logFile == NULL)
  {
    printf("ERRO: falha na abertura do arquivo de saida\n");
    exit(1);
  }

  unsigned int n = 0; //quantidade de elementos;
  unsigned int m = 0; //quantidade de coordenadas;

  char *id;
  char *coordenada;
  bool boolean = true;
  start = clock();
  //Faz a leitura da primeira linha
  qtdChar = getline(&buffer, &bufsize, inputFile);

  while (qtdChar >= 0)
  {
    n++;

    //Le o id;
    id = strtok(buffer, comma);

    //Conta a qtd de coordenadas
    while ((coordenada = strtok(NULL, comma)) != NULL && boolean)
    {
      m++;
    }
    boolean = false;

    qtdChar = getline(&buffer, &bufsize, inputFile);
  }
  //Reinicia leitura do arquivo de entrada
  rewind(inputFile);

  qtdChar = getline(&buffer, &bufsize, inputFile);

  double vetorCoordenadas[m];
  unsigned int posi;
  unsigned int countPoints = 0;

  Point *points[n];

  while (qtdChar >= 0)
  {
    posi = 0;

    //Le o id;
    id = strtok(buffer, comma);

    //Le primeira coordenada;
    coordenada = strtok(NULL, comma);
    while (coordenada != NULL)
    {
      vetorCoordenadas[posi] = atof(coordenada); //armazena a coordenada no vetor;
      posi++;                                    // incrementa posição do vetor;
      coordenada = strtok(NULL, comma);          //Lê a prox coordenada;
    }

    //Cria a Struct do Ponto;
    Point *point = initPoint(point, id, vetorCoordenadas, m);
    points[countPoints] = point;
    countPoints++;

    qtdChar = getline(&buffer, &bufsize, inputFile);
  }

  //ORDENANDO PONTOS LEXICOGRÁFICAMENTE
  qsort(points, n, sizeof(Point *), comparePoints);

  for (int i = 0; i < n; i++)
  {
    fillIdNum(points[i], i);
  }

  for (int i = 0; i < n; i++)
  {
    printf("%d %s \n", returnIdNum(points[i]), returnId(points[i]));
  }

  Edge **arrayEdges = initArrayEdges(n);
  fillEdge(arrayEdges, n, points, m);
  //printArrayEdges(arrayEdges, n, m);

  sortEdges(arrayEdges, n); //ordenando pela distancia entre os pontos src e dst
  //printf("\n\nTEORICAMENTE ORDENADO POR WEIGTH:\n");
  ///printArrayEdges(arrayEdges, n, m);

  Subset **subsetsArray = createSubset(n);

  int counter = 0, flag = 0;
  Edge *result[n - k]; // os Edges restantes para nossa MST

  //while(counter<((n*(n-1)/2) - (k-1))){
  while (flag < n - k)
  {
    Edge *nextEdge = arrayEdges[counter];

    int x = find(subsetsArray, returnIdNum(returnSrc(nextEdge)));
    int y = find(subsetsArray, returnIdNum(returnDst(nextEdge)));

    if (x != y)
    {
      result[flag] = nextEdge;
      flag++;
      Union(subsetsArray, x, y);
    }

    counter++;
  }

  //PRINTANDO ARVORE
  printf("Aqui estão as edges na MST\n");
  int minimumCost = 0;
  for (unsigned int i = 0; i < flag; ++i)
  {
    printf("%s -- %s == %lf\n", returnId(returnSrc(result[i])), returnId(returnDst(result[i])), returnWeigth(result[i]));
    minimumCost += returnWeigth(result[i]);
  }
  printf("Minimum Cost Spanning tree : %d\n", minimumCost);

  //VER O PAI!!!
  // for (unsigned int i = 0; i < n; i++)
  // {
  //   printf("%c PAI: %c\n", 65 + i, 65 + (returnParent(subsetsArray[i])));
  // }

  counter = 0;

  printSameFather(logFile, subsetsArray, points, n);

  // --------------------------DESTRUIÇÕES-----------------------
  destroyArrayEdges(arrayEdges, n, m);

  //destruindo o vetor de pontos
  for (unsigned int i = 0; i < n; i++)
  {
    destroyPoint(points[i]);
  }
  destroySubset(subsetsArray, n);
  //destruindo a matriz
  // destroyMatrix(pointsMatrix, n, n);
  free(buffer);
  fclose(inputFile);
  fclose(logFile);
  stop = clock();
  double time_taken = ((double)stop - start) / CLOCKS_PER_SEC;
  printf("\nTEMPO %.4f\n", time_taken);
  return 0;
}

int comparePoints(const void *a, const void *b)
{
  Point *x = *(Point **)a;
  Point *y = *(Point **)b;

  return strcmp(returnId(x), returnId(y));
}