
#include <stdio.h>
#include <stdlib.h>

double getDoubleInput(char userPrompt[])
{
  double var;
  printf("%s", userPrompt);
  while (scanf("%lf", &var) != 1) {
    printf("Invalid input.\n");
    while (getchar() != '\n');
    printf(%"s", userPrompt);
  }
  return var;
}


int main(void)
{

  return 0;
}