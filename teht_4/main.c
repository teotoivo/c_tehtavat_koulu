#include <stdio.h>


int read_integer(void) {
  int num;
  while (1) {
    printf("Enter positive numbers or negative to stop: ");
    if (scanf("%d", &num) == 1) {
      return num;
    } else {
      printf("invalid input\n");

      while (getchar() != '\n');
    }
  }
}

int main() {
  int sum = 0, count = 0;
  int number;

  while (1) {
    number = read_integer();

    if (number < 0) {
      break;
    }

    sum += number;
    count++;
  }

  if (count > 0) {
    double average = (double)sum / count;
    printf("You entered %d positive numbers. The average is: %.3f\n", count, average);
  } else {
    printf("No positive numbers were entered.\n");
  }

  return 0;
}