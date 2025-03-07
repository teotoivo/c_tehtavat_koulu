#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
  int number;
  struct node *next;
} nnode;

int main()
{
  nnode *head = NULL;
  nnode *tail = NULL;
  char input[100];
  int num;

  printf("Enter numbers or 'end' to stop:\n");

  while (1)
  {
    printf("> ");
    scanf("%99s", input);

    if (strcmp(input, "end") == 0)
    {
      break;
    }

    if (sscanf(input, "%d", &num) == 1)
    {
      nnode *newNode = (nnode *)malloc(sizeof(nnode));
      if (newNode == NULL)
      {
        fprintf(stderr, "Memory allocation failed!\n");
        nnode *current = head;
        while (current != NULL)
        {
          nnode *temp = current;
          current = current->next;
          free(temp);
        }
        return 1;
      }
      newNode->number = num;
      newNode->next = NULL;

      if (head == NULL)
      {
        head = newNode;
        tail = newNode;
      }
      else
      {
        tail->next = newNode;
        tail = newNode;
      }
    }
    else
    {
      printf("Invalid input. Please enter a number or 'end'.\n");
    }
  }

  printf("Entered numbers:\n");
  nnode *current = head;
  while (current != NULL)
  {
    printf("%d ", current->number);
    current = current->next;
  }
  printf("\n");

  current = head;
  while (current != NULL)
  {
    nnode *temp = current;
    current = current->next;
    free(temp);
  }

  return 0;
}
