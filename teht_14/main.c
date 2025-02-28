#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_NAME_SIZE 128
#define MAX_FILE_LINES 100
#define MAX_LINE_LENGTH 80

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
  char lines[MAX_FILE_LINES][MAX_LINE_LENGTH + 1];
  int lineCount = 0;
  FILE *fptr;

  printf("Enter filename: ");

  if (getUserInput(fileNameBuffer, MAX_FILE_NAME_SIZE) == false)
  {
    perror("Error getting user input");
    return EXIT_FAILURE;
  }

  fptr = fopen(fileNameBuffer, "r");
  if (fptr == NULL)
  {
    fprintf(stderr, "Error: Could not open file '%s' for reading\n",
            fileNameBuffer);
    return EXIT_FAILURE;
  }

  while (lineCount < MAX_FILE_LINES &&
         fgets(lines[lineCount], MAX_LINE_LENGTH + 1, fptr) != NULL)
  {
    size_t len = strlen(lines[lineCount]);
    if (len > 0 && lines[lineCount][len - 1] == '\n')
    {
      lines[lineCount][len - 1] = '\0';
    }
    lineCount++;
  }

  fclose(fptr);

  for (int i = 0; i < lineCount; i++)
  {
    for (int j = 0; lines[i][j] != '\0'; j++)
    {
      lines[i][j] = toupper(lines[i][j]);
    }
  }

  fptr = fopen(fileNameBuffer, "w");
  if (fptr == NULL)
  {
    fprintf(stderr, "Error: Could not open file '%s' for writing\n",
            fileNameBuffer);
    return EXIT_FAILURE;
  }

  for (int i = 0; i < lineCount; i++)
  {
    fprintf(fptr, "%s\n", lines[i]);
  }

  fclose(fptr);
  printf("Successfully converted %d lines\n", lineCount);

  return EXIT_SUCCESS;
}
