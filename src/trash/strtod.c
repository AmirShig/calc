#include <stdio.h>
#include <stdlib.h>

int main() {
  char *str = "123.1+10";
  char *endptr;
  double num = strtod(str, &endptr);

  if (endptr == str) {
    printf("Ошибка: Не удалось прочитать число.\n");
  } else {
    printf("Преобразованное число: %lf\n", num);
    // printf("%s\n", endptr);
    str = endptr;
  }
  printf("%s\n", str);

  return 0;
}