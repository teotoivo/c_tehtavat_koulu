#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char getRandomPrintableChar() { return (char)((rand() % 126 - 32) + 32); }

bool generatePassword(char *password, int size, const char *word)
{
  int wordLength = strlen(word);
  int passwordLength = wordLength * 2 + 1;

  if (passwordLength >= size)
  {
    return false;
  }

  password[0] = getRandomPrintableChar();
  for (int i = 0; i < wordLength; i++)
  {
    password[2 * i + 1] = word[i];
    password[2 * i + 2] = getRandomPrintableChar();
  }
  password[passwordLength] = '\0';

  return true;
}

int main()
{
  srand(time(NULL));

  char word[32];
  char password[65];
  printf("Enter a word to place in the password or 'stop' to stop:\n");

  while (1)
  {
    printf("> ");
    scanf("%31s", word);

    if (strcmp(word, "stop") == 0)
    {
      printf("Program stopped.\n");
      break;
    }

    if (generatePassword(password, sizeof(password), word))
    {
      printf("Generated password: %s\n", password);
    }
    else
    {
      printf("Error: Password could not be generated (too long).\n");
    }

    printf("Enter a word to place in the password or 'stop' to stop:\n");
  }

  return 0;
}
