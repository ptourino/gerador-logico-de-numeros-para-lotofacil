/**
  @name    Gerador Logico de Numeros para Lotofacil (GLNL)
  @author  Pedro Augusto Nunes Tourino
  @version 0.5.2710.2911.2023.2 - 27/10/2023 a 29/11/2023

  Dados:
  - opcao de execucao escolhida pelo usuario

  Resultados:
  - execucao de uma opcao por vez a escolha do usuario

  Condicoes:
  - so' aceitara' as opcoes oferecidas.

  Forma de compilacao:
  - Para compilar em terminal (janela de comandos):
    Linux:   gcc -o output/glnl_v0.5.2710.2911.2023.2 ./glnl_v0.5.2710.2911.2023.2.c
    Windows: gcc -o output/glnl_v0.5.2710.2911.2023.2 glnl_v0.5.2710.2911.2023.2.c

  Forma de uso:
  - Para executar em terminal (janela de comandos):
    Linux e Windows: output/glnl_v0.5.2710.2911.2023.2

  Forma alternativa de compilacao e uso:
  - Para executar em terminal (janela de comandos):
    Linux e Windows: ./mk glnl_v0.5.2710.2911.2023.2

    Nota: Ao usar essa alternativa pela primeira
          vez, executar o comando "chmod +x mk".
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define ROWS 5
#define COLUMNS 5
#define MIN_PROBABILITY 1          // mudar
#define MAX_PROBABILITIES_RANGE 10 // mudar
#define MIN_PRIME 5                // mudar
#define MAX_PRIMES_RANGE 2         // mudar
#define MIN_NUMBER 1               // mudar
#define MAX_NUMBERS_RANGE 25       // mudar
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

char generateFileName(char *filename)
{
  char contest[6];

  printf("\n%s ", "Concurso atual:");
  scanf("%s", contest);
  getchar();

  time_t t;
  struct tm *date;

  // Obter a hora atual
  time(&t);

  // Converter a hora atual em uma estrutura de data
  date = localtime(&t);

  char temp[20];

  // Formatar a data como DD-MM-AAAA (por exemplo, 26-10-2023)
  strftime(temp, sizeof(temp), "%d-%m-%Y", date);

  return snprintf(filename, 20, "%s_%s.txt", contest, temp);
}

void saveGame(int *numbers, int size)
{
  char filename[20];

  generateFileName(filename);

  FILE *file = fopen(filename, "at");
  if (file == NULL)
  {
    printf("\n%s %s.", "ERRO: Nao foi possivel abrir o arquivo", filename);
    return;
  }

  for (int index = 0; index < size; index++)
  {
    fprintf(file, "%d ", numbers[index]);
  }
  fprintf(file, "\n\n");

  fclose(file);
}

void generateNumbers(int size) // dividir em funcoes: generateNumbers e createGame
{
  int steeringWheel[ROWS][COLUMNS] = {{1, 2, 3, 4, 5},
                                      {6, 7, 8, 9, 10},
                                      {11, 12, 13, 14, 15},
                                      {16, 17, 18, 19, 20},
                                      {21, 22, 23, 24, 25}};

  int *numbers = (int *)malloc(size * sizeof(int));
  if (numbers == NULL)
  {
    printf("\n%s", "ERRO: Falha na alocacao de memoria.");
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

  /* printf("\nContador de pares = %d", evensCount);
  printf("\nContador de impares = %d", oddsCount);
  printf("\nContador de primos = %d\n", primesCount);

  printf("\nIndex = %d\n", index); */

  saveGame(numbers, size);

  index = 0;

  printf("\n%s\n\n", "Numeros gerados:");
  for (int row = 0; row < ROWS; row++)
  {
    for (int column = 0; column < COLUMNS; column++)
    {
      if (steeringWheel[row][column] == numbers[index])
      {
        if (steeringWheel[row][column] < 10)
        {
          printf("\033[1;38;2;0;255;0m|%d%d|\033[0m ", 0, steeringWheel[row][column]);
        }
        else
        {
          printf("\033[1;38;2;0;255;0m|%d|\033[0m ", steeringWheel[row][column]); // \t
        }

        index++;
      }
      else
      {
        if (steeringWheel[row][column] < 10)
        {
          printf("|%d%d| ", 0, steeringWheel[row][column]);
        }
        else
        {
          printf("|%d| ", steeringWheel[row][column]);
        }
      }
    }
    printf("\n\n");
  }

  free(numbers);

  printf("\n\033[1;38;2;255;0;0m%s\033[0m", "Pressione (ENTER) para continuar");
  getchar();
}

int main(int argc, char *argv[])
{
  enum OPTIONS option = 0;

  do
  {
    clearScreen();

    printf("%s\n", "+-------------------------------------------------------------------+");
    printf("%s\n", "| |||||||||||||||||||||||||||(   GLNL   )|||||||||||||||||||||||||| |");
    printf("%s\n", "+===================================================================+");
    printf("%s\n", "| Menu de opcoes:                                                   |");
    printf("%s\n", "|                                                                   |");
    printf("%s\n", "| (0) - Encerrar o programa                                         |");
    printf("%s\n", "| (1) - Informacoes sobre o programa                                |");
    printf("%s\n", "| ----------------------------------------------------------------- |");
    printf("%s\n", "| (2) - Conferir jogo gerado                                        |");
    printf("%s\n", "| ----------------------------------------------------------------- |");
    printf("%s\n", "| (3) - Gerar jogo com 15 numeros   (6) - Gerar jogo com 18 numeros |");
    printf("%s\n", "| (4) - Gerar jogo com 16 numeros   (7) - Gerar jogo com 19 numeros |");
    printf("%s\n", "| (5) - Gerar jogo com 17 numeros   (8) - Gerar jogo com 20 numeros |");
    printf("%s\n", "+-------------------------------------------------------------------+");

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
      printf("\n\033[1;38;2;255;0;0m%s\033[0m", "Pressione (ENTER) para continuar");
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
      printf("\n\033[1;38;2;255;0;0m%s\033[0m", "Pressione (ENTER) para continuar");
      getchar();
      break;
    }
  } while (option != QUIT);

  printf("\n\n%s", "Pressione (ENTER) para terminar");
  getchar();
  return 0;
}
