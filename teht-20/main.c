#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  int user_debug_level;

  srand(time(NULL));

  printf("Enter debug level (0-4): ");
  if (scanf("%d", &user_debug_level) != 1 || user_debug_level < 0 ||
      user_debug_level > 4)
  {
    printf("Invalid input. Please enter a number between 0 and 4.\n");
    return 1;
  }

  set_debug_level(user_debug_level);

  for (int i = 1; i <= 5; i++)
  {
    int random_debug_level = rand() % 5;
    dprintf(random_debug_level, "Message %d: Debug level %d\n", i,
            random_debug_level);
  }

  return 0;
}
