#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_NAME_SIZE 128
#define MAX_FILE_LINES 40
#define MAX_FILE_LINE_CONTENT 1028

typedef struct menu_item
{
  char name[MAX_FILE_LINE_CONTENT];
  double price;
} menu_item;

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
  char fileNameBuffer[MAX_FILE_LINE_CONTENT];
  printf("Enter file name: ");

  if (getUserInput(fileNameBuffer, MAX_FILE_NAME_SIZE) == false)
  {
    perror("Error getting user input");
    return EXIT_FAILURE;
  }

  FILE *fptr = fopen(fileNameBuffer, "r");
  if (fptr == NULL)
  {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  menu_item menuItemArray[MAX_FILE_LINES];

  char lineBuffer[MAX_FILE_LINE_CONTENT];
  for (int i = 0; i <= MAX_FILE_LINES &&
                  fgets(lineBuffer, MAX_FILE_LINE_CONTENT, fptr) != NULL;
       i++)
  {
    char *semicolonPtr = strchr(lineBuffer, ';');

    if (semicolonPtr == NULL)
    {
      perror("Incorrect file formatting");
      return EXIT_FAILURE;
    }
    int splitLocation = semicolonPtr - lineBuffer;

    strlcpy(menuItemArray[i].name, lineBuffer, MAX_FILE_LINE_CONTENT);
    menuItemArray[i].name[splitLocation] = '\0';

    char priceBuffer[MAX_FILE_LINE_CONTENT];
    strlcpy(priceBuffer, lineBuffer + splitLocation + 2, MAX_FILE_LINE_CONTENT);
    menuItemArray[i].price = strtod(priceBuffer, NULL);
  }
  fclose(fptr);

  printf("%8s\t%s\n", "Price", "Name");
  printf(
      "   _____________________________________________________________________"
      "______________\n");
  for (int i = 0; true; i++)
  {
    if (menuItemArray[i].price == 0.0 && strcmp(menuItemArray[i].name, "") == 0)
    {
      break;
    }
    printf("%8.2f\t%s\n", menuItemArray[i].price, menuItemArray[i].name);
  }

  return EXIT_SUCCESS;
}
