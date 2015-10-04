/**
 * A command line program for converting infix arithmetic expressions
 * into postfix expressions
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
    char data;
    struct stack *next;
} Stack;

Stack* new_stack();
char peek(Stack*);
char pop(Stack**);
void push(Stack**, char);
int is_operand(char);
int precedence(char);
void print_stack(Stack*);

char operators[] = { '-', '+', '/', '*', '^' };
int op_len = 5;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage:\n\tpostfix \"<expression>\"\n");
        return 1;
    }

    Stack *stack = new_stack();
    char c;
    int i = 0;

    while ((c = argv[1][i++]) != '\0') {
        if (c == ' ') {
            continue;
        } else if (is_operand(c)) {
            printf("%c ", c);
        } else if (stack == NULL || peek(stack) == '(') {
            push(&stack, c);
        } else if (c == ')') {
            while ((c = pop(&stack)) != '(')
                printf("%c ", c);
        } else if (precedence(c) >= precedence(peek(stack))) {
            push(&stack, c);
        } else if (precedence(c) < precedence(peek(stack))) {
            while (stack != NULL && precedence(c) < precedence(peek(stack)))
                printf("%c ", pop(&stack));
            push(&stack, c);
        }
    }

    while (stack != NULL) {
        printf("%c ", stack->data);
        pop(&stack);
    }

    printf("\n");
}

int is_operand(char c) {
    if (c == '(' || c == ')')
        return 0;
    for (int i = 0; i < op_len; i++)
        if (operators[i] == c)
            return 0;
    return 1;

}

int precedence(char op) {
    for (int i = 0; i < op_len; i++)
        if (operators[i] == op)
            return i;
    return -1;
}


Stack* new_stack() {
    Stack *stack = NULL;
    return stack;
}

char peek(Stack *stack) {
    return stack->data;
}

char pop(Stack **stack) {
    Stack *top = *stack;
    char c = top->data;
    *stack = top->next;
    free(top);
    return c;
}

void push(Stack **stack, char data) {
    Stack *top = malloc(sizeof(Stack));
    top->data = data;
    top->next = *stack;
    *stack = top;
}

// helper method
void print_stack(Stack *stack) {
    while (stack != NULL) {
        printf("%c\n", stack->data);
        stack = stack->next;
    }
}

