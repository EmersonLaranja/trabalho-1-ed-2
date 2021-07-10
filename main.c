#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char const *argv[])
{

  char *buffer;
  const char s[2] = ","; //onde havera o split;
  size_t bufsize = 0;
  size_t qtdChar;

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

  buffer = (char *)malloc(bufsize * sizeof(char));
  if (buffer == NULL)
  {
    perror("Falha ao alocar buffer");
    exit(1);
  }

  unsigned int n = 0; //quantidade de elementos;
  unsigned int m = 0; //quantidade de coordenadas;

  char *id;
  char *coordenada;
  char *stringPrimeirasCoordenadas;

  //Faz a leitura da primeira linha
  qtdChar = getline(&buffer, &bufsize, inputFile);

  //Le o id;
  id = strtok(buffer, ",");

  //Conta a qtd de coordenadas
  while ((coordenada = strtok(NULL, ",")) != NULL)
  {
    m++;
  }
  printf("M: %d\n", m);

  //Reinicia leitura do arquivo de entrada
  rewind(inputFile);

  qtdChar = getline(&buffer, &bufsize, inputFile);

  double vetorCoordenadas[m];
  unsigned int posi;

  while (qtdChar > 0)
  {
    posi = 0;
    n++;

    //Le o id;
    id = strtok(buffer, ",");

    //Le primeira coordenada;
    coordenada = strtok(NULL, ",");
    while (coordenada != NULL)
    {
      vetorCoordenadas[posi] = atof(coordenada); //armazena a coordenada no vetor;
      posi++;                                    // incrementa posição do vetor;
      coordenada = strtok(NULL, ",");            //Lê a prox coordenada;
    }

    printf("%s ", id);
    for (unsigned int i = 0; i < m; i++)
    {
      printf("%lf ", vetorCoordenadas[i]);
    }
    printf("\n");

    qtdChar = getline(&buffer, &bufsize, inputFile);
    //Cria a Struct do Ponto;
    //segue a vida fml
  }

  return 0;
}
