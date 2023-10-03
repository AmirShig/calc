#include "smart_calc.h"

void create_stack(stack_t *stack) { stack->top = NULL; }

int is_empty(stack_t *stack) { return (stack->top = NULL); }

int push(Node *head, Lex value) {
  errnum error_code = SUCCESS;
  Node *tmp = calloc(1, sizeof(Node));
  if (tmp == NULL) {
    error_code = FAILURE;
  } else {
    tmp->val = value;
    tmp->next = head;
    head = tmp;
  }
  // Node stack->next = ;
  return error_code;
}

double pop(Node *stack) {}