#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>


#define PI 3.14159265

typedef enum {
    NUMBER,
    OPERATOR,
    FUNCTION
} TokenType;

typedef struct {
    TokenType type;
    union {
        double value;
        char op;
        char func[10];
    };
} Token;

typedef struct {
    Token *data;
    int size;
    int top;
} Stack;

Stack* initStack(int size) {
    Stack *stack = malloc(sizeof(Stack));
    stack->data = malloc(size * sizeof(Token));
    stack->size = size;
    stack->top = -1;
    return stack;
}

void push(Stack *stack, Token token) {
    if (stack->top == stack->size - 1) {
        stack->size *= 2;
        stack->data = realloc(stack->data, stack->size * sizeof(Token));
    }
    stack->data[++stack->top] = token;
}

Token pop(Stack *stack) {
    return stack->data[stack->top--];
}

Token peek(Stack *stack) {
    return stack->data[stack->top];
}

int isStackEmpty(Stack *stack) {
    return stack->top == -1;
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

Token* tokenize(char *expression, int *length) {
    Token *tokens = malloc(100 * sizeof(Token));
    int tokenCount = 0;
    for (int i = 0; i < strlen(expression); i++) {
        if (expression[i] == ' ') {
            continue;
        } else if (isdigit(expression[i]) || expression[i] == '.') {
            tokens[tokenCount].type = NUMBER;
            sscanf(expression + i, "%lf", &(tokens[tokenCount].value));
            while (isdigit(expression[i]) || expression[i] == '.') i++;
            i--;
        } else if (isalpha(expression[i])) {
            tokens[tokenCount].type = FUNCTION;
            int j = 0;
            while (isalpha(expression[i])) {
                tokens[tokenCount].func[j++] = expression[i++];
            }
            tokens[tokenCount].func[j] = '\0';
            i--;
        } else {
            tokens[tokenCount].type = OPERATOR;
            tokens[tokenCount].op = expression[i];
        }
        tokenCount++;
    }
    *length = tokenCount;
    return tokens;
}

Token* shuntingYard(Token *tokens, int length, int *outputLength) {
    Stack *operators = initStack(100);
    Token *output = malloc(100 * sizeof(Token));
    int outputCount = 0;

    for (int i = 0; i < length; i++) {
        if (tokens[i].type == NUMBER) {
            output[outputCount++] = tokens[i];
        } else if (tokens[i].type == FUNCTION) {
            push(operators, tokens[i]);
        } else if (tokens[i].type == OPERATOR) {
            while (!isStackEmpty(operators) && precedence(peek(operators).op) >= precedence(tokens[i].op)) {
                output[outputCount++] = pop(operators);
            }
            push(operators, tokens[i]);
        } else if (tokens[i].op == '(') {
            Token t;
            t.type = OPERATOR;
            t.op = '(';
            push(operators, t);
        } else if (tokens[i].op == ')') {
            while (peek(operators).op != '(') {
                output[outputCount++] = pop(operators);
            }
            pop(operators);
        }
    }

    while (!isStackEmpty(operators)) {
        output[outputCount++] = pop(operators);
    }

    *outputLength = outputCount;
    return output;
}

double evaluate(Token *tokens, int length) {
    Stack *values = initStack(100);

    for (int i = 0; i < length; i++) {
        if (tokens[i].type == NUMBER) {
            push(values, tokens[i]);
        } else if (tokens[i].type == OPERATOR) {
            double b = pop(values).value;
            double a = pop(values).value;
            Token result;
            result.type = NUMBER;
            switch (tokens[i].op) {
                case '+':
                    result.value = a + b;
                    break;
                case '-':
                    result.value = a - b;
                    break;
                case '*':
                    result.value = a * b;
                    break;
                case '/':
                    result.value = a / b;
                    break;
            }
            push(values, result);
        } else if (tokens[i].type == FUNCTION) {
            double value = pop(values).value;
            Token result;
            result.type = NUMBER;
            if (strcmp(tokens[i].func, "sin") == 0) {
                result.value = sin(value * PI / 180.0);
            } else if (strcmp(tokens[i].func, "cos") == 0) {
                result.value = cos(value * PI / 180.0);
            } else if (strcmp(tokens[i].func, "tan") == 0) {
                result.value = tan(value * PI / 180.0);
            } else if (strcmp(tokens[i].func, "sqrt") == 0) {
                result.value = sqrt(value);
            }
            push(values, result);
        }
    }

    return pop(values).value;
}

int main() {
    char expression[1000];
    printf("Enter the expression: ");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = '\0';

    int length;
    Token *tokens = tokenize(expression, &length);
    int outputLength;
    Token *postfixTokens = shuntingYard(tokens, length, &outputLength);

    double result = evaluate(postfixTokens, outputLength);
    printf("Result: %lf\n", result);

    free(tokens);
    free(postfixTokens);
    return 0;
}


