#include "read.h"

void verifyArgsLength(int numArgs)
{
  if (numArgs < 4)
  {
    printf("ERRO: Quantidade de argumentos inválidos\n");
    exit(1);
  }

  if (numArgs <= 1)
  {
    printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
    exit(1);
  }
}
void fileWasOpened(FILE *file)
{
  if (file == NULL)
  {
    printf("ERRO: falha na abertura do arquivo de entrada\n");
    exit(1);
  }
}
void getNMvalues(FILE *file, int *n, int *m)
{
  char *id;
  char *coord;
  bool boolean = true;
  char *buffer = NULL;
  size_t bufsize = 0;
  ssize_t qtdChar = 0;
  const char comma[2] = ","; //onde havera o split exigido pelo strtok;

  qtdChar = getline(&buffer, &bufsize, file);

  while (qtdChar >= 0)
  {
    ++*n;
    //Le o id;
    id = strtok(buffer, comma);

    //Conta a qtd de coords
    while ((coord = strtok(NULL, comma)) != NULL && boolean)
    {
      ++*m;
    }
    boolean = false;

    qtdChar = getline(&buffer, &bufsize, file);
  }
  free(buffer);
}