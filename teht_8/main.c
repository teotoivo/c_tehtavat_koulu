#include "stdio.h"
#include "time.h"
#include "stdlib.h"

void printNumbers(const int *array, int count)
{
  for (int i = 0; i < count; i++)
  {
    printf("%d\n", array[i]);
  }
}

int main()
{
  srand(time(NULL));

  int len = 15;

  int array[len];

  for (int i = 0; i < len; i++)
  {
    array[i] = rand();
  }

  printNumbers(array, 15);

  return 0;
}