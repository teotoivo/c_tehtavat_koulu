#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRING_LENGTH 100
#define MAX_CAR_DATA 100

typedef struct
{
  char make[MAX_STRING_LENGTH];
  char model[MAX_STRING_LENGTH];
  struct tm purchase_date;
  struct tm selling_date;
  float mileage_km;
  float purchase_price;
  float selling_price;
  bool has_been_sold;
} CarData;

typedef struct CarNode
{
  CarData data;
  struct CarNode *next;
} CarNode;

void free_cars(CarNode *head);
void clear_terminal();
void print_header();
int get_user_choice();
void clear_input_buffer();
void wait_for_enter();
bool add_new_car(CarNode **head);
bool get_user_input(char *buffer, size_t size);
bool get_date_from_user(struct tm *date);
void list_all_cars(CarNode *head);
char *format_date(int day, int month, int year);

int main(void)
{
  CarNode *head = NULL;
  int choice;

  // for debbugging add a couple cars by default
  CarData car1 = {
      .make = "Toyota",
      .model = "Corolla",
      .mileage_km = 15000.0,
      .purchase_price = 20000.0,
      .has_been_sold = false,
      .purchase_date = {.tm_year = 2022 - 1900, .tm_mon = 1 - 1, .tm_mday = 15}
      // 15-01-2022
  };

  CarData car2 = {
      .make = "Honda",
      .model = "Civic",
      .mileage_km = 25000.0,
      .purchase_price = 22000.0,
      .has_been_sold = true,
      .selling_price = 21000.0,
      .purchase_date = {.tm_year = 2021 - 1900,
                        .tm_mon = 5 - 1,
                        .tm_mday = 10}, // 10-05-2021
      .selling_date = {.tm_year = 2022 - 1900, .tm_mon = 6 - 1, .tm_mday = 20}
      // 20-06-2022
  };

  // Create nodes for the cars and add them to the list
  CarNode *node1 = malloc(sizeof(CarNode));
  if (node1 == NULL)
    return EXIT_FAILURE; // Check for memory allocation failure
  node1->data = car1;
  node1->next = head;
  head = node1;

  CarNode *node2 = malloc(sizeof(CarNode));
  if (node2 == NULL)
    return EXIT_FAILURE; // Check for memory allocation failure
  node2->data = car2;
  node2->next = head;
  head = node2;

  while (1)
  {
    print_header();
    choice = get_user_choice();

    switch (choice)
    {
    case 1:
      if (!add_new_car(&head))
      {
        wait_for_enter();
      }
      else
      {
        clear_terminal();
        printf("Car added\n");
        wait_for_enter();
      }
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      list_all_cars(head);
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
  free_cars(head);
}

void free_cars(CarNode *head)
{
  CarNode *current = head;
  CarNode *next;
  while (current != NULL)
  {
    next = current->next;
    free(current);
    current = next;
  }
  head = NULL;
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
int get_user_choice()
{
  int choice;
  char input[MAX_STRING_LENGTH];

  printf("Enter your choice (1-8): ");

  if (fgets(input, sizeof(input), stdin) == NULL)
  {
    return -1;
  }

  return strtol(input, NULL, 10);
}

float get_float()
{
  float choice;
  char input[MAX_STRING_LENGTH];

  if (fgets(input, sizeof(input), stdin) == NULL)
  {
    return -1;
  }

  return strtof(input, NULL);
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

bool add_new_car(CarNode **head)
{
  CarNode *car_node = malloc(sizeof(CarNode));
  char input_buffer[MAX_STRING_LENGTH];

  clear_terminal();
  printf("========================================\n");
  printf("                ADD A CAR               \n");
  printf("========================================\n\n");

  printf("Car make: ");
  get_user_input(input_buffer, MAX_STRING_LENGTH);
  strcpy(car_node->data.make, input_buffer);

  printf("Car model: ");
  get_user_input(input_buffer, MAX_STRING_LENGTH);
  strcpy(car_node->data.model, input_buffer);

  printf("Car mileage (in km): ");
  int mileage_km = get_float();
  if (mileage_km < 0)
  {
    printf("Invalid mileage\n");
    free(car_node);
    return false;
  }
  car_node->data.mileage_km = mileage_km;

  printf("Car buy date:");
  if (get_date_from_user(&car_node->data.purchase_date) == false)
  {
    free(car_node);
    return false;
  }

  printf("Car buy price (in euro): ");
  int buy_price = get_float();
  car_node->data.purchase_price = buy_price;

  printf("Has the car been sold (y/n): ");
  char hasCarBeenSold = getchar();
  clear_input_buffer();
  if (hasCarBeenSold == 'y' || hasCarBeenSold == 'Y')
  {
    car_node->data.has_been_sold = true;
    printf("Car sell date:");
    get_date_from_user(&car_node->data.selling_date);

    printf("Car sell price (in euro): ");
    int sell_price = get_float();
    car_node->data.selling_price = sell_price;
  }
  else if (hasCarBeenSold == 'n' || hasCarBeenSold == 'N')
  {
    car_node->data.has_been_sold = false;
  }
  else
  {
    printf("Invalid sold status\n");
    free(car_node);
    return false;
  }

  car_node->next = *head;
  *head = car_node;

  return true;
}

bool get_user_input(char *buffer, size_t size)
{
  if (buffer == NULL || size <= 0)
  {
    return false;
  }

  if (fgets(buffer, size, stdin) == NULL)
  {
    return false;
  }

  char *newLine = strchr(buffer, '\n');
  if (newLine != NULL)
  {
    *newLine = '\0';
  }
  else
  {
    while (getchar() != '\n')
      ;
  }

  return true;
}

bool get_date_from_user(struct tm *date)
{
  char input[11];
  time_t now = time(NULL);

  struct tm *local = localtime(&now);
  date->tm_year = local->tm_year;
  date->tm_mon = local->tm_mon;
  date->tm_mday = local->tm_mday;

  printf("Enter a date (24:1:2025) or press Enter for today: ");
  fgets(input, sizeof(input), stdin);

  if (strlen(input) > 1)
  {
    int day, month, year;
    if (sscanf(input, "%d:%d:%d", &day, &month, &year) == 3)
    {
      date->tm_year = year - 1900;
      date->tm_mon = month - 1;
      date->tm_mday = day;
    }
    else
    {
      printf("Invalid date format.");
      return false;
    }
  }

  return true;
}
void list_all_cars(CarNode *head)
{
  clear_terminal();
  printf("====================================================================="
         "=========="
         "========================================\n");
  printf("                                          CAR INVENTORY LIST         "
         "          "
         "                                      \n");
  printf("====================================================================="
         "=========="
         "========================================\n");
  printf("%-15s %-15s %-15s %-15s %-15s %-15s %-15s %-15s\n", "Make", "Model",
         "Purchase Date", "Sell Date", "Mileage", "Buy Price", "Sell Price",
         "Status");
  printf("---------------------------------------------------------------------"
         "----------"
         "----------------------------------------\n");

  if (head == NULL)
  {
    printf("\nNo cars in inventory.\n\n");
  }
  else
  {
    CarNode *current = head;
    char purchase_date_str[12];
    char sell_date_str[12];
    int car_count = 0;
    float total_investment = 0.0;
    float total_revenue = 0.0;
    float total_profit = 0.0;
    int sold_count = 0;

    while (current != NULL)
    {
      // Format purchase date
      sprintf(purchase_date_str, "%02d/%02d/%d",
              current->data.purchase_date.tm_mday,
              current->data.purchase_date.tm_mon + 1,
              current->data.purchase_date.tm_year + 1900);

      // Format sell date if car has been sold
      if (current->data.has_been_sold)
      {
        sprintf(sell_date_str, "%02d/%02d/%d",
                current->data.selling_date.tm_mday,
                current->data.selling_date.tm_mon + 1,
                current->data.selling_date.tm_year + 1900);
        sold_count++;
        total_revenue += current->data.selling_price;
        total_profit +=
            (current->data.selling_price - current->data.purchase_price);
      }
      else
      {
        strcpy(sell_date_str, "N/A");
      }

      total_investment += current->data.purchase_price;

      // Print car information with aligned columns
      printf("%-15s %-15s %-15s %-15s %-15.1f €%-14.2f ", current->data.make,
             current->data.model, purchase_date_str, sell_date_str,
             current->data.mileage_km, current->data.purchase_price);

      if (current->data.has_been_sold)
      {
        printf("€%-14.2f %-15s\n", current->data.selling_price, "Sold");
      }
      else
      {
        printf("%-15s %-15s\n", "N/A", "In Stock");
      }

      current = current->next;
      car_count++;
    }

    printf("-------------------------------------------------------------------"
           "------------"
           "----------------------------------------\n");
    printf("Total Cars: %d (Sold: %d, In Stock: %d)\n", car_count, sold_count,
           car_count - sold_count);
    printf("Total Investment: €%.2f | Total Revenue: €%.2f | Total Profit: "
           "€%.2f\n",
           total_investment, total_revenue, total_profit);
  }

  printf("====================================================================="
         "=========="
         "========================================\n\n");
  wait_for_enter();
}
