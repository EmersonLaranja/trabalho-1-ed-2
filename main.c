#include "read.h"
#include "list.h"

int main(int argc, char const *argv[])
{
  //verifica se foram passados todos os argumentos
  verifyArgsLength(argc);

  //quantidade de grupos desejados
  unsigned int k = atoi(argv[2]);

  // Verifica abertura de arquivos;
  FILE *inputFile = fopen(argv[1], "r");
  fileWasOpened(inputFile);

  FILE *logFile = fopen(argv[3], "w");
  fileWasOpened(logFile);

  //quantidade de elementos;
  unsigned int n = 0;
  //quantidade de coordenadas;
  unsigned int m = 0;

  getNMvalues(inputFile, &n, &m);
  // //Reinicia leitura do arquivo de entrada
  rewind(inputFile);

  Point *points[n];
  initPointArray(points, inputFile, m);

  //ordenando pontos lexicográficamente
  sortPoints(points, n);

  //id numerico usado para comparação no union/find
  fillIdNum(points, n);

  //vetor com as arestas que unem os pontos
  Edge **arrayEdges = initArrayEdges(n);

  fillEdge(arrayEdges, n, points, m);

  //ordenando pela distancia entre os pontos src e dst
  sortEdges(arrayEdges, n);

  Subset **subsetsArray = createSubset(n);

  int maxSizeResult = n - k;

  Edge **result = (Edge **)malloc(sizeof(Edge *) * maxSizeResult);

  //montando o array de arestas
  kruskal(result, subsetsArray, arrayEdges, maxSizeResult, n);

  List *groupsList[k];

  //criando e preenchendo os grupos a serem impressos
  createGroupList(groupsList, subsetsArray, points, k, n);

  //ordenando os grupos lexicográficamente
  sortLists(groupsList, k);

  //imprimindo grupos na saída
  printGroupList(groupsList, k, logFile);

  // --------------------------DESTRUIÇÕES-----------------------

  //destruindo grupos de listas
  destroyGroupList(groupsList, k);

  destroyArrayEdges(arrayEdges, n, m);
  //destruindo o vetor de pontos
  destroyPointsArray(points, n);

  destroySubset(subsetsArray, n);

  //liberando vetor de arestas resultantes do kruskal
  free(result);

  fclose(inputFile);

  fclose(logFile);
  return 0;
}
