#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_NAME_SIZE 128
#define MAX_FILE_CONTENT 10000

bool getUserInput(char *buffer, size_t size)
{
  if (buffer == NULL || size <= 0)
  {
    return false;
  }

  if (fgets(buffer, size, stdin) == NULL)
  {
    return false;
  }

  char *newLine = strchr(buffer, '\n');
  if (newLine != NULL)
  {
    *newLine = '\0';
  }
  else
  {
    while (getchar() != '\n')
      ;
  }

  return true;
}

int main(void)
{
  char fileNameBuffer[MAX_FILE_NAME_SIZE];
  printf("Enter file name: ");
  if (getUserInput(fileNameBuffer, MAX_FILE_NAME_SIZE) == false)
  {
    return EXIT_FAILURE;
  }
  printf("%s", fileNameBuffer);

  FILE *fptr = fopen(fileNameBuffer, "r");
  if (fptr == NULL)
  {
    fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    perror("fopen");
    return EXIT_FAILURE;
  }

  char fileContentBuffer[MAX_FILE_CONTENT];
  fgets(fileContentBuffer, MAX_FILE_CONTENT, fptr);
  int counter = 0;
  int highest = INT_MIN;
  int lowest = INT_MAX;
  for (size_t i = 0; fileContentBuffer[i] != '\0'; i++)
  {
    char currentChar = fileContentBuffer[i];
    if (isdigit(currentChar))
    {
      int digitValue = currentChar - '0';

      counter += digitValue;

      if (digitValue > highest)
      {
        highest = digitValue;
      }
      if (digitValue < lowest)
      {
        lowest = digitValue;
      }
    }
  }
  printf("Count: %d\nLowest: %d\nHighest: %d", counter, lowest, highest);

  fclose(fptr);
  return EXIT_SUCCESS;
}
