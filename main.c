#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
  char *token;
  char *buffer;
  size_t bufsize = 32;
  size_t characters;

  unsigned int k;

  //mensagens de erro

  if (argc < 4)
  {
    printf("ERRO: Quantidade de argumentos inválidos\n");
    return 0;
  }

  if (argc <= 1)
  {
    printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
    return 0;
  }

  //Transforma o K (char) da leitura em unisgned int;
  k = atoi(argv[2]);

  // Verifica abertura de arquivos;
  FILE *file = fopen(argv[1], 'r');

  if (file == NULL)
  {
    printf("ERRO: falha na abertura do arquivo de entrada\n");
    return 0;
  }
  FILE *log = fopen(argv[3], 'w');

  if (log == NULL)
  {
    printf("ERRO: falha na abertura do arquivo de saida\n");
    return 0;
  }

  buffer = (char *)malloc(bufsize * sizeof(char));
  if (buffer == NULL)
  {
    perror("Falha ao alocar buffer");
    exit(1);
  }

  while (file != EOF)
  {
    // getline(, , file);
  }

  return 0;
}
