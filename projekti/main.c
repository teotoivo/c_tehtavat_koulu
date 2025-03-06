#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRING_LENGTH 100
#define MAX_CAR_DATA 100

typedef struct
{
  int id;
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

// - negative value if a < b
// - zero if a == b
// - positive value if a > b
typedef int (*CompareFunc)(const CarData *a, const CarData *b);

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
void print_profit_report(CarNode **head);
CarNode *insertionSort(CarNode *head, CompareFunc compare);
int compare_profits_desending(const CarData *a, const CarData *b);
bool search_cars(CarNode *head);
void stringToLower(char *str);
bool stringContains(const char *str, const char *substr);
int generate_unique_id(CarNode *head);
bool search_car_by_id(CarNode *head);
bool sell_car(CarNode *head);

void initialize_test_data(CarNode **head);

int main(void)
{
  srand(time(NULL));
  CarNode *head = NULL;
  int choice;

  initialize_test_data(&head);

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
      print_profit_report(&head);
      break;
    case 3:
      list_all_cars(head);
      break;
    case 4:
      search_cars(head);
      break;
    case 5:
      search_car_by_id(head);
      break;
    case 6:
      sell_car(head);
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

void initialize_test_data(CarNode **head)
{
  srand(time(NULL));

  const char *car_makes[] = {"Toyota",   "Honda",  "Ford",  "BMW",
                             "Mercedes", "Audi",   "Volvo", "Volkswagen",
                             "Nissan",   "Hyundai"};
  const char *car_models[][5] = {
      {"Corolla", "Camry", "RAV4", "Prius", "Highlander"},
      {"Civic", "Accord", "CR-V", "Pilot", "Fit"},
      {"Focus", "Fiesta", "Mustang", "Explorer", "F-150"},
      {"3 Series", "5 Series", "X3", "X5", "i8"},
      {"C-Class", "E-Class", "S-Class", "GLC", "GLE"},
      {"A3", "A4", "Q5", "Q7", "TT"},
      {"S60", "XC60", "XC90", "V60", "S90"},
      {"Golf", "Passat", "Tiguan", "Polo", "Jetta"},
      {"Altima", "Sentra", "Rogue", "Pathfinder", "Maxima"},
      {"Elantra", "Sonata", "Tucson", "Santa Fe", "Kona"}};

  time_t now = time(NULL);
  struct tm *current_time = localtime(&now);
  int current_year = current_time->tm_year;
  int current_month = current_time->tm_mon;

  for (int i = 0; i < 10; i++)
  {
    CarNode *new_car = malloc(sizeof(CarNode));
    if (new_car == NULL)
    {
      printf("Memory allocation failed\n");
      return;
    }

    new_car->data.id = generate_unique_id(*head);

    int make_index = rand() % 10;
    int model_index = rand() % 5;

    strcpy(new_car->data.make, car_makes[make_index]);
    strcpy(new_car->data.model, car_models[make_index][model_index]);

    new_car->data.mileage_km = 5000.0 + (rand() % 145000);

    int purchase_years_ago = 1 + (rand() % 3);
    int purchase_months_ago = rand() % 12;

    new_car->data.purchase_date = *current_time;
    new_car->data.purchase_date.tm_year = current_year - purchase_years_ago;
    new_car->data.purchase_date.tm_mon =
        (current_month - purchase_months_ago + 12) % 12;
    new_car->data.purchase_date.tm_mday = 1 + (rand() % 28);

    new_car->data.purchase_price = 5000.0 + (rand() % 45000);

    new_car->data.has_been_sold = (rand() % 10) < 7;

    if (new_car->data.has_been_sold)
    {
      int sell_months_after_purchase =
          1 + (rand() % (purchase_years_ago * 12 + purchase_months_ago - 1));

      new_car->data.selling_date = new_car->data.purchase_date;
      new_car->data.selling_date.tm_mon += sell_months_after_purchase;
      while (new_car->data.selling_date.tm_mon > 11)
      {
        new_car->data.selling_date.tm_mon -= 12;
        new_car->data.selling_date.tm_year++;
      }
      new_car->data.selling_date.tm_mday = 1 + (rand() % 28);

      float profit_factor = 0.9 + ((float)rand() / (float)RAND_MAX) * 0.5;
      new_car->data.selling_price =
          new_car->data.purchase_price * profit_factor;
    }
    else
    {
      // Default values for unsold cars
      new_car->data.selling_price = 0.0;
    }

    new_car->next = *head;
    *head = new_car;
  }
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
  printf("3. List all cars\n");
  printf("4. Search cars\n");
  printf("5. Search car by id\n");
  printf("6. Sell a car\n");
  printf("7. Backup database\n");
  printf("8. Exit\n\n");
}
int get_user_choice()
{
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

  car_node->data.id = generate_unique_id(*head);

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
  printf("%-10s %-15s %-15s %-15s %-15s %-15s %-15s %-15s %-15s\n", "ID",
         "Make", "Model", "Purchase Date", "Sell Date", "Mileage", "Buy Price",
         "Sell Price", "Status");
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
      sprintf(purchase_date_str, "%02d/%02d/%d",
              current->data.purchase_date.tm_mday,
              current->data.purchase_date.tm_mon + 1,
              current->data.purchase_date.tm_year + 1900);

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

      printf("%-10d %-15s %-15s %-15s %-15s %-15.1f €%-14.2f ",
             current->data.id, current->data.make, current->data.model,
             purchase_date_str, sell_date_str, current->data.mileage_km,
             current->data.purchase_price);

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

void print_profit_report(CarNode **head)
{
  *head = insertionSort(*head, compare_profits_desending);

  clear_terminal();
  printf("====================================================================="
         "=========="
         "========================================\n");
  printf("                                          CAR PROFIT RAPORT         "
         "          "
         "                                      \n");
  printf("====================================================================="
         "=========="
         "========================================\n");
  printf("%-10s %-15s %-15s %-15s %-15s %-15s %-15s\n", "ID", "Make", "Model",
         "Buy Price", "Sell Price", "Status", "Profit");
  printf("---------------------------------------------------------------------"
         "----------"
         "----------------------------------------\n");

  if (head == NULL)
  {
    printf("\nNo cars in inventory.\n\n");
  }
  else
  {
    CarNode *current = *head;
    int car_count = 0;
    float total_investment = 0.0;
    float total_revenue = 0.0;
    float total_profit = 0.0;
    int sold_count = 0;

    while (current != NULL)
    {

      total_investment += current->data.purchase_price;

      printf("%-10d %-15s %-15s €%-14.2f ", current->data.id,
             current->data.make, current->data.model,
             current->data.purchase_price);

      if (current->data.has_been_sold)
      {
        printf("€%-14.2f %-15s €%-14.2f\n", current->data.selling_price, "Sold",
               current->data.selling_price - current->data.purchase_price);
        total_revenue += current->data.selling_price;
        total_profit +=
            current->data.selling_price - current->data.purchase_price;
        sold_count += 1;
      }
      else
      {
        printf("%-15s %-15s %-15s\n", "N/A", "In Stock", "N/A");
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
CarNode *insertionSort(CarNode *head, CompareFunc compare)
{
  if (head == NULL || head->next == NULL)
  {
    return head;
  }

  CarNode *sorted = NULL;
  CarNode *current = head;

  while (current != NULL)
  {
    CarNode *next = current->next;

    if (sorted == NULL || compare(&sorted->data, &current->data) >= 0)
    {
      current->next = sorted;
      sorted = current;
    }
    else
    {
      CarNode *temp = sorted;

      while (temp->next != NULL &&
             compare(&temp->next->data, &current->data) < 0)
      {
        temp = temp->next;
      }
      current->next = temp->next;
      temp->next = current;
    }
    current = next;
  }
  return sorted;
}

int compare_profits_desending(const CarData *a, const CarData *b)
{
  if (!a->has_been_sold && !b->has_been_sold)
    return 0;
  if (a->has_been_sold && !b->has_been_sold)
    return -1;
  if (b->has_been_sold && !a->has_been_sold)
    return 1;

  int profit_a = a->selling_price - a->purchase_price;
  int profit_b = b->selling_price - b->purchase_price;

  return profit_b - profit_a;
}

bool search_cars(CarNode *head)
{
  clear_terminal();
  printf("========================================\n");
  printf("            SEARCH FOR CARS            \n");
  printf("========================================\n\n");

  printf("Search make or model: ");
  char input_buffer[MAX_STRING_LENGTH];
  get_user_input(input_buffer, MAX_STRING_LENGTH);

  char search_term[MAX_STRING_LENGTH];
  strcpy(search_term, input_buffer);
  for (int i = 0; search_term[i]; i++)
  {
    search_term[i] = tolower(search_term[i]);
  }

  CarNode *current = head;
  int count = 0;

  printf("\nSearch Results:\n");
  printf("----------------------------------------\n");

  while (current != NULL)
  {
    char make_lower[MAX_STRING_LENGTH];
    char model_lower[MAX_STRING_LENGTH];

    strcpy(make_lower, current->data.make);
    strcpy(model_lower, current->data.model);

    for (int i = 0; make_lower[i]; i++)
    {
      make_lower[i] = tolower(make_lower[i]);
    }

    for (int i = 0; model_lower[i]; i++)
    {
      model_lower[i] = tolower(model_lower[i]);
    }

    if (strstr(make_lower, search_term) != NULL ||
        strstr(model_lower, search_term) != NULL)
    {

      printf("ID: %d\n", current->data.id);
      printf("Make: %s\n", current->data.make);
      printf("Model: %s\n", current->data.model);
      printf("Stock Status: %s\n",
             current->data.has_been_sold ? "In Stock" : "Sold");
      printf("Buy Price: $%.2f\n", current->data.purchase_price);
      if (current->data.has_been_sold)
      {
        printf("Price sold: %.2f\n", current->data.selling_price);
      }
      printf("----------------------------------------\n");
      count++;
    }

    current = current->next;
  }

  if (count == 0)
  {
    printf("No cars matching '%s' were found.\n", input_buffer);
  }
  else
  {
    printf("\nFound %d car(s) matching '%s'.\n", count, input_buffer);
  }

  printf("\nPress Enter to continue...");
  get_user_input(input_buffer, MAX_STRING_LENGTH);

  return true;
}

void stringToLower(char *str)
{
  for (int i = 0; str[i]; i++)
  {
    str[i] = tolower(str[i]);
  }
}

bool stringContains(const char *str, const char *substr)
{
  if (str == NULL || substr == NULL)
  {
    return false; // Handle null pointers
  }

  char strLower[strlen(str) + 1];
  strcpy(strLower, str);
  stringToLower(strLower);

  char substrLower[strlen(substr) + 1];
  strcpy(substrLower, substr);
  stringToLower(substrLower);

  return strstr(strLower, substrLower) != NULL;
}
int generate_unique_id(CarNode *head)
{
  int new_id;
  bool id_exists;

  do
  {
    new_id = 1000 + rand() % 9000;

    id_exists = false;
    CarNode *current = head;
    while (current != NULL)
    {
      if (current->data.id == new_id)
      {
        id_exists = true;
        break;
      }
      current = current->next;
    }
  } while (id_exists);

  return new_id;
}

bool search_car_by_id(CarNode *head)
{
  clear_terminal();
  printf("========================================\n");
  printf("            SEARCH CAR BY ID           \n");
  printf("========================================\n\n");

  printf("Enter car ID: ");
  char input_buffer[MAX_STRING_LENGTH];
  get_user_input(input_buffer, MAX_STRING_LENGTH);

  int search_id = strtol(input_buffer, NULL, 10);

  if (search_id <= 0)
  {
    printf("\nInvalid ID. Please enter a valid number.\n");
    wait_for_enter();
    return false;
  }

  CarNode *current = head;
  bool found = false;

  while (current != NULL)
  {
    if (current->data.id == search_id)
    {
      found = true;

      char purchase_date_str[12];
      char sell_date_str[12];

      sprintf(purchase_date_str, "%02d/%02d/%d",
              current->data.purchase_date.tm_mday,
              current->data.purchase_date.tm_mon + 1,
              current->data.purchase_date.tm_year + 1900);

      if (current->data.has_been_sold)
      {
        sprintf(sell_date_str, "%02d/%02d/%d",
                current->data.selling_date.tm_mday,
                current->data.selling_date.tm_mon + 1,
                current->data.selling_date.tm_year + 1900);
      }
      else
      {
        strcpy(sell_date_str, "N/A");
      }

      printf("\n========================================\n");
      printf("            CAR DETAILS                \n");
      printf("========================================\n\n");

      printf("%-20s: %d\n", "ID", current->data.id);
      printf("%-20s: %s\n", "Make", current->data.make);
      printf("%-20s: %s\n", "Model", current->data.model);
      printf("%-20s: %s\n", "Purchase Date", purchase_date_str);
      printf("%-20s: %.1f km\n", "Mileage", current->data.mileage_km);
      printf("%-20s: €%.2f\n", "Purchase Price", current->data.purchase_price);

      if (current->data.has_been_sold)
      {
        printf("%-20s: %s\n", "Selling Date", sell_date_str);
        printf("%-20s: €%.2f\n", "Selling Price", current->data.selling_price);
        float profit =
            current->data.selling_price - current->data.purchase_price;
        printf("%-20s: €%.2f\n", "Profit", profit);
        printf("%-20s: %s\n", "Status", "Sold");
      }
      else
      {
        printf("%-20s: %s\n", "Selling Date", "N/A");
        printf("%-20s: %s\n", "Selling Price", "N/A");
        printf("%-20s: %s\n", "Profit", "N/A");
        printf("%-20s: %s\n", "Status", "In Stock");
      }

      break;
    }
    current = current->next;
  }

  if (!found)
  {
    printf("\nNo car with ID %d was found.\n", search_id);
  }

  printf("\n");
  wait_for_enter();
  return true;
}

bool sell_car(CarNode *head)
{
  clear_terminal();
  printf("========================================\n");
  printf("              SELL A CAR               \n");
  printf("========================================\n\n");

  printf("Enter the ID of the car to sell: ");
  char input_buffer[MAX_STRING_LENGTH];
  get_user_input(input_buffer, MAX_STRING_LENGTH);

  int car_id = strtol(input_buffer, NULL, 10);

  CarNode *current = head;
  bool found = false;

  while (current != NULL)
  {
    if (current->data.id == car_id)
    {
      found = true;

      if (current->data.has_been_sold)
      {
        printf("\nThis car has already been sold.\n");
        wait_for_enter();
        return false;
      }

      // Get selling date
      printf("\nSelling date:\n");
      get_date_from_user(&current->data.selling_date);

      // Get selling price
      printf("Selling price (in euro): ");
      float selling_price = get_float();

      // Update car data
      current->data.selling_price = selling_price;
      current->data.has_been_sold = true;

      float profit = current->data.selling_price - current->data.purchase_price;

      printf("\nCar ID %d sold for €%.2f (Profit: €%.2f)\n", current->data.id,
             current->data.selling_price, profit);

      wait_for_enter();
      return true;
    }
    current = current->next;
  }

  if (!found)
  {
    printf("\nNo car with ID %d was found.\n", car_id);
    wait_for_enter();
  }

  return false;
}
