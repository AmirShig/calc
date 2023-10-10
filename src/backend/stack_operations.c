#include "smart_calc.h"

void create_stack(stack_tt *stack) { stack->top = NULL; }

int is_empty(stack_tt *stack) {
  int result = 0;
  if (stack->top == NULL) result = 1;
  return result;
}

int push(stack_tt *head, Lex *value) {
  errnum error_code = SUCCESS;
  Node *new_node = (Node *)calloc(1, sizeof(Node));
  if (new_node == NULL) {
    error_code = MALLOC_ERR;
  } else {
    new_node->val.val = value->val;
    new_node->val.priority = value->priority;
    new_node->val.unary = value->unary;
    new_node->next = head->top;
    head->top = new_node;
  }
  return error_code;
}

int pop(stack_tt *stack, Lex *result) {
  errnum error_code = SUCCESS;
  if (is_empty(stack)) {
    error_code = EMPTY_STACK;
  } else {
    Node *node_tmp = stack->top;
    if (result != NULL) {
      result->val = node_tmp->val.val;
      result->unary = node_tmp->val.unary;
    }
    stack->top = node_tmp->next;
    free(node_tmp);
  }
  return error_code;
}

// int pick(stack_tt *stack, double *result) {}