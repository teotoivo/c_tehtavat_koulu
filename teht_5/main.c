#include <stdio.h>

int read_range(int low, int high) {
  int number;
  while (1) {
    printf("Enter a number between %d and %d: ", low, high);
    if (scanf("%d", &number) == 1) {
      if (number >= low && number <= high) {
        return number;
      } else {
        printf("Error: Number must be between %d and %d. Try again.\n", low, high);
      }
    } else {
      printf("Error: Invalid input. Please enter a number.\n");
      while (getchar() != '\n');
    }
  }
}

int main() {
  printf("Let's play!\n");

  for (int round = 1; round <= 3; round++) {
    printf("Roll a die and enter your result.\n");
    int user_roll = read_range(1, 6);

    int program_roll;
    if (user_roll == 6) {
      program_roll = 6;
      printf("I got %d. It is a tie!\n", program_roll);
    } else {
      program_roll = user_roll + 1;
      printf("I got %d. I win!\n", program_roll);
    }
  }

  printf("Better luck next time. Bye!\n");
  return 0;
}