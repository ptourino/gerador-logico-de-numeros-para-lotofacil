/**
  @name    Gerador Logico de Numeros para Lotofacil (GLNL)
  @author  Pedro Augusto Nunes Tourino
  @version 0.2.1309.1210.2023.2 - 13/09/2023 a 12/10/2023

  Dados:
  - opcao de execucao escolhida pelo usuario

  Resultados:
  - execucao de uma opcao por vez a escolha do usuario

  Condicoes:
  - so' aceitara' as opcoes oferecidas.

  Forma de compilacao:
  - Para compilar em terminal (janela de comandos):
    Linux: 	 gcc -o output/glnl_v0.2.1309.1210.2023.2 ./glnl_v0.2.1309.1210.2023.2.c
    Windows: gcc -o output/glnl_v0.2.1309.1210.2023.2 glnl_v0.2.1309.1210.2023.2.c

  Forma de uso:
  - Para executar em terminal (janela de comandos):
    Linux e Windows: output/glnl_v0.2.1309.1210.2023.2

  Forma alternativa de compilacao e uso:
  - Para executar em terminal (janela de comandos):
    Linux e Windows: ./mk glnl_v0.2.1309.1210.2023.2

    Nota: Ao usar essa alternativa pela primeira
          vez, executar o comando "chmod +x mk".
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *a, const void *b)
{
  return (*(int *)a - *(int *)b);
}

int isEqual(int quantity, int number, int numbers[])
{
  for (int index = 0; index < quantity; index++)
  {
    if (numbers[index] == number)
    {
      return 1;
    }
  }
  return 0;
}

int isEven(int number)
{
  return number % 2 == 0;
}

void generateNumbers(int quantity)
{
  srand(time(NULL));

  int *numbers = malloc(quantity * sizeof(int)),
      number = 0,
      even = 0,
      evenCount = 0,
      odd = 0,
      oddCount = 0,
      percent = (rand() % 10) + 1,
      index = 0;

  if (numbers == NULL)
  {
    printf("%s\n", "ERRO: Falha na alocacao de memoria.");
    exit(1);
  }

  if (percent <= 5)
  {
    even = 7;
    odd = 8;
  }
  else if (percent <= 7)
  {
    even = 8;
    odd = 7;
  }
  else if (percent <= 9)
  {
    even = 6;
    odd = 9;
  }
  else
  {
    even = 9;
    odd = 6;
  }

  printf("\n%s", "+----------------------------------------------+");
  printf("\n%s %d %s", "|               Gerar", quantity, "numeros               |");
  printf("\n%s", "+==============================================+");
  do
  {
    number = (rand() % 25) + 1;

    if (!isEqual(quantity, number, numbers))
    {
      if (isEven(number) && evenCount < even)
      {
        numbers[index] = number;
        evenCount++;
        index++;
      }
      else if (!isEven(number) && oddCount < odd)
      {
        numbers[index] = number;
        oddCount++;
        index++;
      }
    }
  } while (index < quantity);

  qsort(numbers, quantity, sizeof(int), compare);

  printf("\n(%d)  %s ", even, "Pares  :");
  for (index = 0; index < quantity; index++)
  {
    if (isEven(numbers[index]))
    {
      printf("%d ", numbers[index]);
    }
  }

  printf("\n(%d)  %s ", odd, "Impares:");
  for (index = 0; index < quantity; index++)
  {
    if (!isEven(numbers[index]))
    {
      printf("%d ", numbers[index]);
    }
  }

  printf("\n(%d) %s ", quantity, "Numeros:");
  for (index = 0; index < quantity; index++)
  {
    printf("%d ", numbers[index]);
  }

  printf("\n\n%s %d %s", "Jogo com", quantity, "numeros");
  // printf("\n%s %.2f", "Valor: R$", gamePrice(quantity));
  printf("\n%s", "Obs. : Valor correspondente 'a data e hora: 16/09/2023 'as 7h30.");
  printf("\n%s\n\n", "       De acordo com Loterias CAIXA: https://loterias.caixa.gov.br/Paginas/Lotofacil.aspx");

  free(numbers);
}

int main(void)
{
  int option = 0;

  do
  {
    printf("\n%s", "+----------------------------------------------+");
    printf("\n%s", "|      GNL (Gerador de Numeros Lotofacil)      |");
    printf("\n%s", "|         versao: 0.2.1309.1210.2023.2         |");
    printf("\n%s", "+==============================================+");
    printf("\n%s", "| Opcoes:                                      |");
    printf("\n%s", "|                                              |");
    printf("\n%s", "| 0 - Encerrar programa                        |");
    printf("\n%s", "| 1 - Informacoes do programa                  |");
    printf("\n%s", "| -------------------------------------------- |");
    printf("\n%s", "| 2 - Gerar 15 numeros    5 - Gerar 18 numeros |");
    printf("\n%s", "| 3 - Gerar 16 numeros    6 - Gerar 19 numeros |");
    printf("\n%s", "| 4 - Gerar 17 numeros    7 - Gerar 20 numeros |");
    printf("\n%s", "+----------------------------------------------+");

    printf("\n\n%s ", "Opcao:");
    scanf("%d", &option);
    getchar();

    switch (option)
    {
    case 0:
      printf("%s", "Encerrar programa.");
      break;
    case 1:
      printf("\n%s\n", "Autor: Pedro Augusto Nunes Tourino");
      break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
      generateNumbers(option + 13);
      break;
    default:
      printf("%s\n", "ERRO: Opcao invalida. Tente novamente.");
      break;
    }
  } while (option != 0);

  printf("\n\n%s\n", "Apertar ENTER para terminar");
  getchar();
  return 0;
}
