#include "stdio.h"
#include "stdlib.h"
#include <string.h>

int main()
{
  char buffer[50] = {0};

  while (1)
  {
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
      printf("Error reading input.\n");
      continue;
    }
    if (strchr(buffer,'\n') == NULL)
    {
      while (getchar() != '\n');
    }
    if (strcmp("stop", buffer) == 0)
    {
      printf("Stopping\n");
      break;
    }
    printf("Length of the string: %llu\n", strlen(buffer) - 1);
  }

  return 0;
}