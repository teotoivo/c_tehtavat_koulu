#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_menu() {
  printf("Select an operation:\n");
  printf("1. Roll D6\n");
  printf("2. Roll D10\n");
  printf("3. Quit\n");
}

int roll_d6() {
  return rand() % 6 + 1;
}

int roll_d10() {
  return rand() % 10 + 1;
}

int get_user_choice() {
  int choice;
  while (1) {
    printf("Enter your choice (1-3): ");
    if (scanf("%d", &choice) == 1) {
      if (choice >= 1 && choice <= 3) {
        return choice;
      } else {
        printf("Error: Choice must be between 1 and 3. Try again.\n");
      }
    } else {
      printf("Error: Invalid input. Please enter a number.\n");
      while (getchar() != '\n');
    }
  }
}

int main() {
  srand(time(NULL));

  while (1) {
    print_menu();
    int choice = get_user_choice();

    switch (choice) {
    case 1:
      printf("You rolled a D6: %d\n", roll_d6());
      break;
    case 2:
      printf("You rolled a D10: %d\n", roll_d10());
      break;
    case 3:
      printf("Quitting the program. Goodbye!\n");
      return 0; // Exit the program
    default:
      printf("Invalid choice. This should never happen!\n");
      break;
    }
  }

  return 0;
}