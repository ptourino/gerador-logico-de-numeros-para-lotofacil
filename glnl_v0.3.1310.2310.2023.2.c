/**
  @name    Gerador Logico de Numeros para Lotofacil (GLNL)
  @author  Pedro Augusto Nunes Tourino
  @version 0.3.1310.2310.2023.2 - 13/10/2023 a 23/10/2023

  Dados:
  - opcao de execucao escolhida pelo usuario

  Resultados:
  - execucao de uma opcao por vez a escolha do usuario

  Condicoes:
  - so' aceitara' as opcoes oferecidas.

  Forma de compilacao:
  - Para compilar em terminal (janela de comandos):
    Linux: 	 gcc -o output/glnl_v0.3.1310.2310.2023.2 ./glnl_v0.3.1310.2310.2023.2.c
    Windows: gcc -o output/glnl_v0.3.1310.2310.2023.2 glnl_v0.3.1310.2310.2023.2.c

  Forma de uso:
  - Para executar em terminal (janela de comandos):
    Linux e Windows: output/glnl_v0.3.1310.2310.2023.2

  Forma alternativa de compilacao e uso:
  - Para executar em terminal (janela de comandos):
    Linux e Windows: ./mk glnl_v0.3.1310.2310.2023.2

    Nota: Ao usar essa alternativa pela primeira
          vez, executar o comando "chmod +x mk".
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MIN_PROBABILITY 1
#define MAX_PROBABILITIES_RANGE 10
#define MIN_PRIME 5
#define MAX_PRIMES_RANGE 2
#define MIN_NUMBER 1
#define MAX_NUMBERS_RANGE 25
#define OPTION (option + 13)

enum OPTIONS
{
  QUIT = 0,
  INFO = 1,
  GENERATE_15 = 2,
  GENERATE_16 = 3,
  GENERATE_17 = 4,
  GENERATE_18 = 5,
  GENERATE_19 = 6,
  GENERATE_20 = 7
} option;

int compare(const void *a, const void *b)
{
  return (*(int *)a - *(int *)b);
}

bool isEven(int number)
{
  if (number % 2 == 0)
  {
    return true;
  }

  return false;
}

bool isPrime(int number)
{
  if (number <= 1)
  {
    return false;
  }

  for (int index = 2; index * index <= number; index++)
  {
    if (number % index == 0)
    {
      return false;
    }
  }

  return true;
}

bool isRepeated(const int *numbers, int size, int number)
{
  for (int index = 0; index < size; index++)
  {
    if (numbers[index] == number)
    {
      return true;
    }
  }

  return false;
}

/**
  Metodo para limpar a saida de dados padrao.
*/
void clearScreen()
{
#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
  system("cls");
#elif defined(__linux__)
  system("clear");
#elif defined(__APPLE__) && defined(__MACH__)
  system("clear");
#elif defined(unix) || defined(__unix__) || defined(__unix)
  system("clear");
#else
#error Unknown_OS
#endif
}

void generateNumbers(int size)
{
  int *numbers = (int *)malloc(size * sizeof(int));

  if (numbers == NULL)
  {
    printf("\n%s\n", "ERRO: Falha na alocacao de memoria. Tente novamente.");
    return;
  }

  srand(time(NULL));

  int primes = (rand() % MAX_PRIMES_RANGE) + MIN_PRIME,
      probability = (rand() % MAX_PROBABILITIES_RANGE) + MIN_PROBABILITY,
      evens = (probability <= 5)   ? 7
              : (probability <= 7) ? 8
              : (probability <= 9) ? 6
                                   : 9,
      odds = size - evens;

  int number = 0,
      primesCount = 0,
      evensCount = 0,
      oddsCount = 0,
      index = 0;

  if (evens + odds != size)
  {
    do
    {
      number = (rand() % MAX_NUMBERS_RANGE) + MIN_NUMBER;

      if (!isRepeated(numbers, size, number))
      {
        numbers[index] = number;
        index++;
      }
    } while (index < size - (evens + odds));
  }

  do
  {
    number = (rand() % MAX_NUMBERS_RANGE) + MIN_NUMBER;

    if (!isRepeated(numbers, size, number))
    {
      if (isPrime(number))
      {
        numbers[index] = number;
        primesCount++;
        index++;

        if (isEven(number))
        {
          evensCount++;
        }
        else
        {
          oddsCount++;
        }
      }
    }
  } while (primesCount < primes);

  do
  {
    number = (rand() % MAX_NUMBERS_RANGE) + MIN_NUMBER;

    if (!isRepeated(numbers, size, number) && !isPrime(number))
    {
      if (isEven(number) && evensCount < evens)
      {
        numbers[index] = number;
        evensCount++;
        index++;
      }
      else if (!isEven(number) && oddsCount < odds)
      {
        numbers[index] = number;
        oddsCount++;
        index++;
      }
    }
  } while (index < size);

  qsort(numbers, size, sizeof(int), compare);

  printf("Pares = %d", evens);
  printf("\nImpares = %d", odds);
  printf("\nPrimos = %d\n", primes);

  printf("\nContador de pares = %d", evensCount);
  printf("\nContador de impares = %d", oddsCount);
  printf("\nContador de primos = %d\n", primesCount);

  printf("\nIndex = %d\n\n", index);

  for (index = 0; index < size; index++)
  {
    printf("%d ", numbers[index]);
  }

  free(numbers);

  printf("\n\n%s", "Pressione (ENTER) para continuar");
  getchar();
}

int main(void)
{
  enum OPTIONS option = 0;

  do
  {
    clearScreen();

    printf("%s\n", "+--------------------------------------------------+");
    printf("%s\n", "| ||||||||||||||||||(   GLNL   )|||||||||||||||||| |");
    printf("%s\n", "+==================================================+");
    printf("%s\n", "| Menu de opcoes:                                  |");
    printf("%s\n", "|                                                  |");
    printf("%s\n", "| (0) - Encerrar o programa                        |");
    printf("%s\n", "| (1) - Informacoes sobre o programa               |");
    printf("%s\n", "| ------------------------------------------------ |");
    printf("%s\n", "| (2) - Gerar 15 numeros    (5) - Gerar 18 numeros |");
    printf("%s\n", "| (3) - Gerar 16 numeros    (6) - Gerar 19 numeros |");
    printf("%s\n", "| (4) - Gerar 17 numeros    (7) - Gerar 20 numeros |");
    printf("%s\n", "+--------------------------------------------------+");

    printf("\n%s ", "Opcao:");
    scanf("%d", &option);
    getchar();

    switch (option)
    {
    case QUIT:
      clearScreen();
      printf("%s", "Encerrando o programa...");
      break;
    case INFO:
      clearScreen();
      printf("%s\n", "Autor: Pedro Augusto Nunes Tourino");
      printf("%s\n", "GLNL ou Gerador logico de Numeros para Lotofacil");
      printf("\n%s", "Pressione (ENTER) para continuar");
      getchar();
      break;
    case GENERATE_15:
    case GENERATE_16:
    case GENERATE_17:
    case GENERATE_18:
    case GENERATE_19:
    case GENERATE_20:
      clearScreen();
      generateNumbers(OPTION);
      break;
    default:
      clearScreen();
      printf("%s\n", "ERRO: Opcao invalida. Tente novamente.");
      printf("\n%s", "Pressione (ENTER) para continuar");
      getchar();
      break;
    }
  } while (option != QUIT);

  printf("\n\n%s", "Pressione (ENTER) para terminar");
  getchar();
  return 0;
}
