
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
int getIntInput(char userPrompt[])
{
  int var;
  printf("%s", userPrompt);
  while (scanf("%i", &var) != 1) {
    printf("Invalid input.\n");
    while (getchar() != '\n');
    printf(%"s", userPrompt);
  }
  return var;
}


int main(void)
{
  int numberOfStudents = getIntInput("How many students: ");
  int studentsArr[numberOfStudents];
  for (int i = 0; i < numberOfStudents; i++)
  {
    studentsArr[i] = -1;
  }

  return 0;
}