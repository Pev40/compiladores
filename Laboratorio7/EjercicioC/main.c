#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXSTACK 100
#define MAXLEN 100

typedef struct {
    int top;
    int items[MAXSTACK];
} Stack;

void initialize(Stack *s) {
    s->top = -1;
}

int is_empty(Stack *s) {
    return s->top == -1;
}

int is_full(Stack *s) {
    return s->top == MAXSTACK - 1;
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

void infix_to_postfix(char* infix, char* postfix) {
    Stack s;
    initialize(&s);
    char* token = infix;
    int j = 0;
    while (*token) {
        if (isdigit(*token)) {
            while (isdigit(*token)) {
                postfix[j++] = *token++;
            }
            postfix[j++] = ' ';
        } else if (*token == '(') {
            push(&s, *token++);
        } else if (*token == ')') {
            while (!is_empty(&s) && s.items[s.top] != '(') {
                postfix[j++] = pop(&s);
                postfix[j++] = ' ';
            }
            pop(&s);  // Pop '('
            token++;
        } else if (*token == '+' || *token == '-' || *token == '*' || *token == '/') {
            while (!is_empty(&s) && s.items[s.top] != '(' &&
                   ((s.items[s.top] == '*' || s.items[s.top] == '/') || 
                    (s.items[s.top] == '+' || s.items[s.top] == '-'))) {
                postfix[j++] = pop(&s);
                postfix[j++] = ' ';
            }
            push(&s, *token++);
        } else {
            token++;
        }
    }
    while (!is_empty(&s)) {
        postfix[j++] = pop(&s);
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
}

int evaluate_postfix(char* postfix) {
    Stack s;
    initialize(&s);
    char* token = strtok(postfix, " ");
    while (token != NULL) {
        if (isdigit(token[0])) {
            push(&s, atoi(token));
        } else {
            int operand2 = pop(&s);
            int operand1 = pop(&s);
            switch (token[0]) {
                case '+': push(&s, operand1 + operand2); break;
                case '-': push(&s, operand1 - operand2); break;
                case '*': push(&s, operand1 * operand2); break;
                case '/': push(&s, operand1 / operand2); break;
                default: printf("Unknown operator: %c\n", token[0]); exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " ");
    }
    return pop(&s);
}

int main() {
    FILE *file = fopen("programa1.txt", "r");
    if (!file) {
        printf("Could not open file\n");
        return 1;
    }

    char line[MAXLEN];
    char postfix[MAXLEN];
    int result;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "INICIO", 6) == 0 || strncmp(line, "FIN", 3) == 0) {
            continue;
        }

        // Remove the semicolon at the end of the line if it exists
        char *semicolon = strchr(line, ';');
        if (semicolon) {
            *semicolon = '\0';
        }

        infix_to_postfix(line, postfix);
        printf("Postfix: %s\n", postfix);
        result = evaluate_postfix(postfix);
        printf("Result: %d\n", result);
    }

    fclose(file);
    return 0;
}
