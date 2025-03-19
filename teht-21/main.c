#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

unsigned char compute_checksum(const char *sentence)
{
  unsigned char checksum = 0;
  while (*sentence && *sentence != '*')
  {
    checksum ^= *sentence;
    sentence++;
  }
  return checksum;
}

int main()
{
  char filename[256];
  char line[MAX_LINE_LENGTH];
  FILE *file;

  printf("Enter the file name: ");
  scanf("%255s", filename);

  file = fopen(filename, "r");
  if (!file)
  {
    perror("Error opening file");
    return 1;
  }

  while (fgets(line, sizeof(line), file))
  {
    if (line[0] == '$')
    {
      char *asterisk = strchr(line, '*');
      if (asterisk)
      {
        *asterisk = '\0';
        unsigned char calculated_checksum = compute_checksum(line + 1);

        int given_checksum;
        sscanf(asterisk + 1, "%2x", &given_checksum);

        if (calculated_checksum == given_checksum)
        {
          printf("[ OK ] %s\n", line);
        }
        else
        {
          printf("[FAIL] %s\n", line);
        }
      }
    }
  }

  fclose(file);
  return 0;
}
