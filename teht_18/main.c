#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  int userInput;

  // Seed the random number generator
  srand(time(NULL));

  while (1)
  {
    printf("Enter a number between 0 and 15 (or a negative number to stop): ");
    scanf("%d", &userInput);

    if (userInput < 0)
    {
      printf("Exiting program.\n");
      break;
    }

    if (userInput >= 0 && userInput <= 15)
    {
      int randomNumber = rand();

      printf("Random number (hex): 0x%X\n", randomNumber);

      int shiftedNumber = randomNumber >> userInput;

      int maskedNumber = shiftedNumber & 0x3F; // 0x3F is 63 in decimal, which
                                               // is 111111 in binary

      printf("Result (hex): 0x%02X\n", maskedNumber);
    }
    else
    {
      printf("Invalid input. Please enter a number between 0 and 15 or a "
             "negative number.\n");
    }
  }

  return 0;
}
