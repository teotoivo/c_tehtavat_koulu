#include <stdio.h>
#include <string.h>

int count_words(const char* str, const char* word) {
  int count = 0;
  int word_len = strlen(word);
  const char* temp = str;

  while ((temp = strstr(temp, word)) != NULL) {
    count++;
    temp += word_len;
  }

  return count;
}

int main() {
  const char* text = "hello world, hello again!";
  const char* word = "hello";

  int result = count_words(text, word);
  printf("The word '%s' appears %d times.\n", word, result);

  return 0;
}
