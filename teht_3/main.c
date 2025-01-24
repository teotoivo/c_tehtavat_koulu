
#include <stdio.h>
#include <stdlib.h>

double getDoubleInput(char userPrompt[])
{
  double var;
  printf("%s", userPrompt);
  while (scanf("%lf", &var) != 1) {
    printf("Invalid input.\n");
    while (getchar() != '\n');
    printf("%s", userPrompt);
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
    printf("%s", userPrompt);
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
  for (int i = 0; i < numberOfStudents; i++)
  {
    int studentNumber;
    while (1)
    {
      char prompt[50];
      sprintf(prompt, "Enter student number (1 - %i): ", numberOfStudents);
      studentNumber = getIntInput(prompt);
      if (studentNumber >= 1 && studentNumber <= numberOfStudents)
      {
        break;
      }

      printf("Invalid input.\n");
    }

    int studentGrade;
    while (1)
    {
      studentGrade = getIntInput("Enter student grade (0 - 5): ");
      if (studentGrade >= 0 && studentGrade <= 5)
      {
        break;
      }

      printf("Invalid input.\n");
    }

    studentsArr[studentNumber-1] = studentGrade;
  }

  printf("%-10s%s\n", "Student", "Grade");
  for (int i = 0; i < numberOfStudents; i++)
  {
    printf("%-10i%i\n", i+1, studentsArr[i]);
  }

  return 0;
}