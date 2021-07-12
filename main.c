
#include <stdbool.h>
#include "point.h"

void fillMatrix(unsigned int n, double **pointsMatrix, Point **points, unsigned int m);
void printMatrix(unsigned int n, double **pointsMatrix, unsigned int m);
double **initMatrix(int nlines, int ncolumns);
double **destroyMatrix(double **matrix, int nlines, int ncolumns);

int main(int argc, char const *argv[])
{

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

  // Preencher Matriz de distancias
  // double pointsMatrix[n][n];
  double **pointsMatrix = initMatrix(n, n);
  fillMatrix(n, pointsMatrix, points, m);
  // printMatrix(n, pointsMatrix, m);

  for (unsigned int i = 0; i < n; i++)
  {
    destroyPoint(points[i]);
  }

  destroyMatrix(pointsMatrix, n, n);
  free(buffer);
  fclose(inputFile);
  fclose(logFile);
  return 0;
}

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

void printMatrix(unsigned int n, double **pointsMatrix, unsigned int m)
{
  for (unsigned int i = 0; i < n; i++)
  {
    for (unsigned int j = 0; j < i; j++)
    {
      printf("%.2f ", pointsMatrix[i][j]);
    }
    printf("\n");
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
