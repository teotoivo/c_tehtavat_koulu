#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STRING_LENGTH 100
struct CarData
{
  char make[MAX_STRING_LENGTH];
  char model[MAX_STRING_LENGTH];
  float mileage; // in km
  time_t purchase_date;
  float pruchase_price; // in euro
  bool has_been_sold;   // flag to see if the car has been sold
  time_t selling_date;
  float selling_price;
};

void clear_terminal();
void print_header();
int get_menu_choice();
void clear_input_buffer();
void wait_for_enter();

int main(void)
{
  int choice;

  while (1)
  {
    print_header();
    choice = get_menu_choice();

    switch (choice)
    {
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    case 7:
      break;
    case 8:
      return EXIT_SUCCESS;
      break;
    default:
      printf("\nInvalid choice try again.\n");
      wait_for_enter();
      break;
    }
  }
}

void clear_terminal() { system("clear || cls"); }
void print_header()
{
  clear_terminal();
  printf("========================================\n");
  printf("       CAR SALES MANAGEMENT SYSTEM      \n");
  printf("========================================\n\n");
  printf("1. Add a new car\n");
  printf("2. Print profit report (sorted by profit)\n");
  printf("3. Print sell time report (sorted by sell time)\n");
  printf("4. List all cars\n");
  printf("5. Search cars\n");
  printf("6. Sell a car\n");
  printf("7. Backup database\n");
  printf("8. Exit\n\n");
}
int get_menu_choice()
{
  int choice;
  printf("Enter your choice (1-8): ");
  scanf("%d", &choice);
  clear_input_buffer();
  return choice;
}
void clear_input_buffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}
void wait_for_enter()
{
  printf("Press enter to continue...");
  getchar();
}
