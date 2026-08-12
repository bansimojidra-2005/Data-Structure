#include <stdio.h>
#define MAX 100
int main()
{

	void push(char stack[], int *top, char element);
	char pop(char stack[], int *top);
	int priority(char op);
	void infixtopostfix(char s[], int *top);


    char s[MAX];
    int top = -1;

    printf("Enter Infix Expression : ");
    scanf("%s", s);

    printf("Postfix Expression : ");
    infixtopostfix(s, &top);

    return 0;
}

void push(char stack[], int *top, char element)
{
    if (*top == MAX - 1)
    {
        printf("\nStack Overflow");
    }
    else
    {
        (*top)++;
        stack[*top] = element;
    }
}

char pop(char stack[], int *top)
{
    char item;

    if (*top == -1)
    {
        return '\0';
    }

    item = stack[*top];
    (*top)--;

    return item;
}

int priority(char op)
{
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '^')
        return 3;
    else
        return 0;
}

void infixtopostfix(char s[], int *top)
{
    char stack[MAX];
    char postfix[MAX];
    int i = 0, j = 0;
    char ch;

    while (s[i] != '\0')
    {
        ch = s[i];

        if ((ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z') ||
            (ch >= '0' && ch <= '9'))
        {
            postfix[j++] = ch;
        }
        else if (ch == '(')
        {
            push(stack, top, ch);
        }
        else if (ch == ')')
        {
            while (*top != -1 && stack[*top] != '(')
            {
                postfix[j++] = pop(stack, top);
            }

            if (*top != -1)
                pop(stack, top);
        }
        else
        {
            while (*top != -1 && stack[*top]!='(' && priority(stack[*top]) >= priority(ch))
            {
                postfix[j++] = pop(stack, top);
            }

            push(stack, top, ch);
        }

        i++;
    }

    while (*top != -1)
    {
        postfix[j++] = pop(stack, top);
    }

    postfix[j] = '\0';
	printf("%s\n", postfix);
}