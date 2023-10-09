#include "smart_calc.h"

typedef int Data;

typedef struct Node Node;

struct Node {
  Data value;
  Node *next;
};

void print_struct(Node *list) {
  for (Node *p = list; p != NULL; p = p->next) {
    printf("%d\n", p->value);
  }
}

int main() {
  Node a = {0}, b = {0}, c = {0};
  Node *list = &a;
  a.value = 5;
  a.next = &b;

  b.value = 25;
  b.next = &c;

  c.value = 125;
  c.next = NULL;

  print_struct(list);
}