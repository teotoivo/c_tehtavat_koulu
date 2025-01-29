#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int replace_char(char *str, const char *repl){
  int count = 0;

  for (int i = 0; i < strlen(str); i++)
  {
    if (str[i] == repl[0])
    {
      str[i] = repl[1];
      count++;
    }
  }

  return count;
}


int main()
{
  char text[80] = "I am so tired of Python. C is much better language";
  int count = replace_char(text, "e3");

  printf("Replaced %d times\nNew string: \"%s\"", count, text);

  return 0;
}