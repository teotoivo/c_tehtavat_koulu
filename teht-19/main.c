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

int compareByName(const void *a, const void *b)
{
  return strcmp(((menu_item *)a)->name, ((menu_item *)b)->name);
}

int compareByPrice(const void *a, const void *b)
{
  double priceA = ((menu_item *)a)->price;
  double priceB = ((menu_item *)b)->price;
  return (priceA > priceB) - (priceA < priceB);
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
  int itemCount = 0;

  char lineBuffer[MAX_FILE_LINE_CONTENT];
  while (itemCount < MAX_FILE_LINES &&
         fgets(lineBuffer, MAX_FILE_LINE_CONTENT, fptr) != NULL)
  {
    char *semicolonPtr = strchr(lineBuffer, ';');
    if (semicolonPtr == NULL)
    {
      perror("Incorrect file formatting");
      return EXIT_FAILURE;
    }

    int splitLocation = semicolonPtr - lineBuffer;
    strlcpy(menuItemArray[itemCount].name, lineBuffer, splitLocation + 1);

    char priceBuffer[MAX_FILE_LINE_CONTENT];
    strlcpy(priceBuffer, lineBuffer + splitLocation + 2, MAX_FILE_LINE_CONTENT);
    menuItemArray[itemCount].price = strtod(priceBuffer, NULL);

    itemCount++;
  }
  fclose(fptr);

  char sortChoice[10];
  printf("Sort by (name/price): ");
  getUserInput(sortChoice, sizeof(sortChoice));

  if (strcmp(sortChoice, "name") == 0)
  {
    qsort(menuItemArray, itemCount, sizeof(menu_item), compareByName);
  }
  else if (strcmp(sortChoice, "price") == 0)
  {
    qsort(menuItemArray, itemCount, sizeof(menu_item), compareByPrice);
  }
  else
  {
    printf("Invalid sorting option. Displaying unsorted list.\n");
  }

  printf("%8s\t%s\n", "Price", "Name");
  printf("   __________________________________________________________\n");
  for (int i = 0; i < itemCount; i++)
  {
    printf("%8.2f\t%s\n", menuItemArray[i].price, menuItemArray[i].name);
  }

  return EXIT_SUCCESS;
}
