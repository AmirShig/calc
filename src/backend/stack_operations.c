#include "smart_calc.h"

void create_stack(stack_t *stack) { stack->top = NULL; }

int is_empty(stack_t *stack) {
  int result = 0;
  if (stack->top == NULL) result = 1;
  return result;
}

int push(stack_t *head, Lex *value) {
  errnum error_code = SUCCESS;
  Node *new_node = (Node *)calloc(1, sizeof(Node));
  if (new_node == NULL) {
    error_code = MALLOC_ERR;
  } else {
    new_node->val = value->val;
    new_node->priority = value->priority;
    new_node->val_type = value->val_type;
    new_node->next = head->top;
    head->top = new_node;
  }
  return error_code;
}

int pop(stack_t *stack, Lex *result) {
  errnum error_code = SUCCESS;
  if (is_empty(stack)) {
    error_code = EMPTY_STACK;
  } else {
    Node *node_tmp = stack->top;
    // Lex lex_tmp = node_tmp->val;
    result->val = node_tmp->val;

    stack->top = node_tmp->next;
    free(node_tmp);
  }
  return error_code;
}

// int pick(stack_t *stack, double *result) {}