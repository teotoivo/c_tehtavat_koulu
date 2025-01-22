
#include <stdio.h>

int main(void)
{
  printf("Enter price of bus ticket: ");
  double busPrice;
  if (scanf("%lf", &busPrice) != 1 || busPrice < 0) {
    printf("Invalid input. Bus price must be a positive number.\n");
    return 1;
  }

  printf("Enter price of taxi: ");
  double taxiPrice;
  if (scanf("%lf", &taxiPrice) != 1 || taxiPrice < 0) {
    printf("Invalid input. Taxi price must be a positive number.\n");
    return 1;
  }

  printf("How much money do you have: ");
  double money;
  if (scanf("%lf", &money) != 1 || money < 0) {
    printf("Invalid input. Money must be a positive number.\n");
    return 1;
  }
  printf("\nYou have %0.2lf euros left.\n", money);

  int answer;
  while (money >= busPrice || money >= taxiPrice)
  {
    printf("Do you want to take\n");
    printf("\t1) bus (%0.2lf euros)\n", busPrice);
    printf("\t2) taxi (%0.2lf euros)\n", taxiPrice);
    printf("Enter your selection: ");
    if (scanf("%d", &answer) != 1) {
      printf("Invalid input. Please enter a valid option (1 or 2).\n");
      // Clear the input buffer
      while (getchar() != '\n');
      continue;
    }
    switch (answer)
    {
    case 1:
      if (money >= busPrice) {
        printf("You chose bus.\n");
        money -= busPrice;
      } else {
        printf("Not enough money for the bus.\n");
      }
      break;

    case 2:
      if (money >= taxiPrice) {
        printf("You chose taxi.\n");
        money -= taxiPrice;
      } else {
        printf("Not enough money for the taxi.\n");
      }
      break;

    default:
      printf("Invalid option. Please choose 1 or 2.\n");
      break;
    }
    printf("You have %0.2lf euros left.\n", money);
  }
  printf("You need to walk. Bye\n");
  return 0;
}