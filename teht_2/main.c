
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  float arr[12];

  double taxRate;
  printf("Enter tax rate: ");
  while (scanf("%lf", &taxRate) != 1) {
    printf("Invalid input.\n");
    while (getchar() != '\n');
    printf("Enter tax rate: ");
  }


  double incomeLimit;
  printf("Enter income limit: ");
  while (scanf("%lf", &incomeLimit) != 1) {
    printf("Invalid input.\n");
    while (getchar() != '\n');
    printf("Enter income limit: ");
  }

  double taxRateOverLimit;
  printf("Enter tax rate for over the limit: ");
  while (scanf("%lf", &taxRateOverLimit) != 1) {
    printf("Invalid input.\n");
    while (getchar() != '\n');
    printf("Enter tax rate for over the limit: ");
  }


  for (int i = 0; i < 12; i++)
  {
    printf("\nEnter income for month %d: ", i+1);

    while (scanf("%lf", &arr[i]) != 1)
    {
      printf("Invalid input.\n");
      while (getchar() != '\n');
      printf("Enter income for month %d: ", i+1);
    }
  }

  printf("\n");
  printf("%s%12s%12s\n","month", "income", "tax");
  double total = 0;
  for (int i = 0; i < 12; i++)
  {
    double tax = 0;
    total += arr[i];
    if (total <= incomeLimit)
    {
      tax = arr[i] * (taxRate / 100);
    }
    else
    {
      if ((total - arr[i]) <= incomeLimit)
      {
        double overLimit = total - incomeLimit;
        double underLimit = arr[i] - overLimit;

        tax += overLimit * (taxRateOverLimit / 100);
        tax += underLimit * (taxRate / 100);
      }
      else
      {
        tax = arr[i] * (taxRateOverLimit / 100);
      }
    }
    printf("%5i%12.2lf%12.2lf\n", i+1, arr[i], tax);
  }


  return 0;
}