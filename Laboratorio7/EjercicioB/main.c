#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAXSIZE 100

typedef struct {
    int top;
    int items[MAXSIZE];
} Stack;

void initialize(Stack *s) {
    s->top = -1;
}

bool is_empty(Stack *s) {
    return s->top == -1;
}

bool is_full(Stack *s) {
    return s->top == MAXSIZE - 1;
}

void push(Stack *s, int value) {
    if (!is_full(s)) {
        s->items[++s->top] = value;
    } else {
        printf("Stack overflow\n");
        exit(EXIT_FAILURE);
    }
}

int pop(Stack *s) {
    if (!is_empty(s)) {
        return s->items[s->top--];
    } else {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
}

int evaluate_postfix(char *expression) {
    Stack s;
    initialize(&s);
    char *token = strtok(expression, " ");

    while (token != NULL) {
        if (isdigit(token[0])) {
            push(&s, atoi(token));
        } else {
            int operand2 = pop(&s);
            int operand1 = pop(&s);
            switch (token[0]) {
                case '+':
                    push(&s, operand1 + operand2);
                    break;
                case '-':
                    push(&s, operand1 - operand2);
                    break;
                case '*':
                    push(&s, operand1 * operand2);
                    break;
                case '/':
                    if (operand2 == 0) {
                        printf("Division by zero\n");
                        exit(EXIT_FAILURE);
                    }
                    push(&s, operand1 / operand2);
                    break;
                default:
                    printf("Unknown operator: %c\n", token[0]);
                    exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " ");
    }

    if (!is_empty(&s)) {
        return pop(&s);
    } else {
        printf("Invalid expression\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    char expression[100];
    printf("Ingresa Expresion: ");
    fgets(expression, 100, stdin);

    // Remove newline character at the end of the input string
    expression[strcspn(expression, "\n")] = '\0';

    int result = evaluate_postfix(expression);
    printf("Resultado: %d\n", result);

    return 0;
}
