#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

char infix[MAX_SIZE];
char postfix[MAX_SIZE];
char stack[MAX_SIZE];
int top = -1;

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else
        return 0;
}

void push(char op) {
    if (top >= MAX_SIZE - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack[++top] = op;
}

char pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        return '\0';
    }
    return stack[top--];
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

void infixToPostfix() {
    int len = strlen(infix);
    int index = 0;

    for (int i = 0; i < len; i++) {
        char ch = infix[i];
        if (ch == ' ' || ch == '\t') {
            continue;
        } else if (isdigit(ch) || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            postfix[index++] = ch;
        } else if (isOperator(ch)) {
            while (top != -1 && precedence(stack[top]) >= precedence(ch)) {
                postfix[index++] = pop();
            }
            push(ch);
        } else if (ch == '(') {
            push(ch);
        } else if (ch == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[index++] = pop();
            }
            pop(); 
        }
    }

    while (top != -1) {
        postfix[index++] = pop();
    }
    postfix[index] = '\0';
}

int main() {
	printf("Infix to Postfix \n");
    	printf("---------------- \n");
    	printf("Enter expression: ");
    	scanf("%[^\n]", infix);

    	infixToPostfix();

    	printf("Postfix expression: %s\n", postfix);

    return 0;
}
