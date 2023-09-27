#include "smart_calc.h"

void create_stack(Node *stack) { stack->next = NULL; }

int push(Node *head, Lex value) {
  int error_code = SUCCESS;
  Node *tmp = calloc(1, sizeof(Node));
  if (tmp == NULL) {
    error_code = FAILURE;
  } else {
    tmp->val = value;
    tmp->next = head;
    head = tmp;
  }
  // Node stack->next = ;
  return 0;
}

double pop(Node *stack) {}