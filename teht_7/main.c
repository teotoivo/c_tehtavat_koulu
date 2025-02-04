#include <stdio.h>
#include <stdbool.h>

bool read_positive(int *value) {
  int temp;
  printf("Enter a positive number: ");
  if (scanf("%d", &temp) == 1 && temp > 0) {
    *value = temp;
    return true;
  }
  while (getchar() != '\n');
  return false;
}

int main() {
  int guess;
  int incorrect_attempts = 0;
  const int max_attempts = 3;

  printf("Guess how much money I have!\n");

  while (incorrect_attempts < max_attempts) {
    if (read_positive(&guess)) {
      int actual_money = 2 * guess + 20;
      printf("You didn’t get it right. I have %d euros.\n", actual_money);
    } else {
      incorrect_attempts++;
      printf("Incorrect input\n");
    }
    if (incorrect_attempts < max_attempts) {
      printf("Guess how much money I have!\n");
    }
  }

  printf("I give up! See you later!\n");
  return 0;
}
