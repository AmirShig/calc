#include <stdio.h>
#define is_space(c) ((c) == ' ' || (c) == '\t' || (c) == '\n' || (c) == '\r')
#define is_digit(c) ((c) >= '0' && (c) <= '9')
#define ops_calc 1
#define ops_num 2
#define ops_start 3
#define ops_end 4
#define ops_unary 5

int is_math_expr(const char* s) {
  const char* p;
  int st, n = 0;
  //проверка на правильность скобок
  for (p = s; *p; ++p) {
    if (*p == '(')
      ++n;
    else if (*p == ')') {
      if (--n < 0) break;
    }
  }
  if (!*s || (n != 0)) return 0;

  //проверка на правильность арифметического выражения
  for (st = ops_start; *s;) {
    if (is_space(*s)) {
      ++s;
      continue;
    } else if (is_digit(*s)) {
      if (st != ops_start && st != ops_calc && st != ops_unary) return 0;

      while (is_digit(*s)) ++s;
      if (*s == '.') ++s;
      while (is_digit(*s)) ++s;
      st = ops_num;
      continue;
    }

    switch (*s) {
      case '(':
        if (st == ops_num || st == ops_end) return 0;
        st = ops_start;
        break;
      case ')':
        if (st == ops_start || st == ops_calc || st == ops_unary) return 0;
        st = ops_end;
        break;
      case '+':
      case '-':
        switch (st) {
          case ops_unary:
            return 0;
          case ops_start:
          case ops_calc:
            st = ops_unary;
            break;
          case ops_num:
          case ops_end:
            st = ops_calc;
            break;
          default:
            return 0;
        }
        break;
      case '*':
      case '/':
      case '^':
        if (st == ops_start || st == ops_calc || st == ops_unary) return 0;
        st = ops_calc;
        break;
      default:
        return 0;
    }
    ++s;
  }
  return (st == ops_num || st == ops_end);
}

int main(void) {
  char s[] = "(100 * -100^60) * 1.89";
  // double n = -(-100 * -100 / 60) * +1.89;

  if (is_math_expr(s))
    puts("Good.");
  else
    puts("Error expr!");
  getchar();
  return 0;
}