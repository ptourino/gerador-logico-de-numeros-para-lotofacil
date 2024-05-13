/**
  @name    Gerador Logico de Numeros para Lotofacil (GLNL)
  @author  Pedro Augusto Nunes Tourino
  @version 0.1.1209.2023.2 - 01/09/2023 a 12/09/2023

  Dados:
  - opcao de execucao escolhida pelo usuario

  Resultados:
  - execucao de uma opcao por vez a escolha do usuario

  Condicoes:
  - so' aceitara' as opcoes oferecidas.

  Forma de compilacao:
  - Para compilar em terminal (janela de comandos):
    Linux: 	 gcc -o output/glnl_v0.1.1209.2023.2 ./glnl_v0.1.1209.2023.2.c
    Windows: gcc -o output/glnl_v0.1.1209.2023.2 glnl_v0.1.1209.2023.2.c

  Forma de uso:
  - Para executar em terminal (janela de comandos):
    Linux e Windows: output/glnl_v0.1.1209.2023.2

  Forma alternativa de compilacao e uso:
  - Para executar em terminal (janela de comandos):
    Linux e Windows: ./mk glnl_v0.1.1209.2023.2

    Nota: Ao usar essa alternativa pela primeira
          vez, executar o comando "chmod +x mk".
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerarNumeros(int n)
{
  int i, j, igual,
      *v = malloc(n * sizeof(int));

  if (v == NULL)
  {
    printf("ERRO: Falha na alocacao de memoria.\n");
    exit(1);
  }

  for (i = 0; i < n;)
  {
    v[i] = 1 + (rand() % 25);
    igual = 0;

    for (int j = 0; j < i; j++)
    {
      if (v[j] == v[i])
      {
        igual = 1;
      }
    }

    if (igual == 0)
    {
      i++;
    }
  }

  printf("Jogo com %d numeros: ", n);
  for (i = 0; i < n; i++)
  {
    printf("%d ", v[i]);
  }
  printf("\n");

  if (n == 15)
  {
    printf("\nValor: R$ 3,00");
    printf("\nObs .: Valor correspondente 'a data e hora: 16/09/2023 'as 7h30.\n");
    printf("       De acordo com Loterias CAIXA: https://loterias.caixa.gov.br/Paginas/Lotofacil.aspx\n\n");
  }
  else if (n == 16)
  {
    printf("\nValor: R$ 48,00");
    printf("\nObs .: Valor correspondente 'a data e hora: 16/09/2023 'as 7h30.\n");
    printf("       De acordo com Loterias CAIXA: https://loterias.caixa.gov.br/Paginas/Lotofacil.aspx\n\n");
  }
  else if (n == 17)
  {
    printf("\nValor: R$ 408,00");
    printf("\nObs .: Valor correspondente 'a data e hora: 16/09/2023 'as 7h30.\n");
    printf("       De acordo com Loterias CAIXA: https://loterias.caixa.gov.br/Paginas/Lotofacil.aspx\n\n");
  }
  else if (n == 18)
  {
    printf("\nValor: R$ 2.448,00");
    printf("\nObs .: Valor correspondente 'a data e hora: 16/09/2023 'as 7h30.\n");
    printf("       De acordo com Loterias CAIXA: https://loterias.caixa.gov.br/Paginas/Lotofacil.aspx\n\n");
  }
  else if (n == 19)
  {
    printf("\nValor: R$ 11.628,00");
    printf("\nObs .: Valor correspondente 'a data e hora: 16/09/2023 'as 7h30.\n");
    printf("       De acordo com Loterias CAIXA: https://loterias.caixa.gov.br/Paginas/Lotofacil.aspx\n\n");
  }
  else
  {
    printf("\nValor: R$ 46.512,00");
    printf("\nObs .: Valor correspondente 'a data e hora: 16/09/2023 'as 7h30.\n");
    printf("       De acordo com Loterias CAIXA: https://loterias.caixa.gov.br/Paginas/Lotofacil.aspx\n\n");
  }

  free(v);
}

int main(void)
{
  int opcao = 0;

  printf("\nGerador Logico de Numeros para Lotofacil - Programa = v0.1.1209.2023.2");
  printf("\nAutor: Pedro Augusto Nunes Tourino\n");

  srand(time(NULL));

  do
  {
    printf("\nOpcoes:");
    printf("\n0  - Sair");
    printf("\n15 - Jogo com 15 numeros   18 - Jogo com 18 numeros");
    printf("\n16 - Jogo com 16 numeros   19 - Jogo com 19 numeros");
    printf("\n17 - Jogo com 17 numeros   20 - Jogo com 20 numeros");

    printf("\n\nOpcao: ");
    scanf("%d", &opcao);
    getchar();

    if (opcao != 0)
    {
      if (opcao >= 15 && opcao <= 20)
      {
        gerarNumeros(opcao);
      }
      else
      {
        printf("ERRO: Opcao invalida.\n");
      }
    }
    else
    {
      printf("Voce escolheu a opcao sair.\n");
    }
  } while (opcao != 0);

  printf("\nApertar ENTER para terminar\n");
  getchar();
  return 0;
}
