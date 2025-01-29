#include "stdio.h"
#include "time.h"
#include "stdlib.h"

int findFirst(const unsigned int *array, unsigned int what)
{
  int i = 0;
  while (1)
  {
    if (array[i] == 0)
    {
      return -1;
    } else if (array[i] == what)
    {
      return i;
    }
    i++;
  }
}

int main()
{
  srand(time(NULL));
  unsigned int array[20];

  for (int i = 0; i < 19; i++)
  {
    array[i] = rand() % 20 + 1;
  }
  array[19] = 0;

  int answer;

  while (answer != 0)
  {
    printf("What number to find: ");
    while (scanf("%d", &answer) != 1)
    {
      printf("Invalid input!\n");
      while (getchar() != '\n');
    }
    int find = findFirst(array, answer);
    if (find == -1)
    {
      printf("Not found!\n");
    } else
    {
      printf("found at: %d\n", find);
    }
  }

  return 0;
}