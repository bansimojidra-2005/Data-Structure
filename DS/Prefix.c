include <stdio.h>
#define MAX 50

void main()
{
    void push(char st[], char item, int *top);
    char pop(char st[], int *top);
    int priority(char op);
    void infixtoprefix(char s[], int *top);

    char s[MAX];
    int top = -1;

    printf("Enter Infix Expression: ");
    scanf("%s", s);

    printf("Prefix Expression: ");
    infixtoprefix(s, &top);

    return;
}

void push(char st[], char item, int *top)
{
    if (*top == MAX - 1)
    {
        printf("\nStack Overflow");
    }
    else
    {
        *top = *top + 1;
        st[*top] = item;
    }
}

char pop(char st[], int *top)
{
    char item;

    if (*top == -1)
    {
        printf("\nStack Underflow");
        return '\0';
    }

    item = st[*top];
    *top = *top - 1;

    return item;
}

int priority(char op)
{
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else
        return 0;
}

void infixtoprefix(char s[], int *top)
{
    int len;
    int i;
    int k;
    char ch;
    char st[MAX];
    char result[MAX];

    len = 0;
    k = 0;

    while (s[len] != '\0')
    {
        len++;
    }

    for (i = len - 1; i >= 0; i--)
    {
        ch = s[i];

        if (ch == ')')
        {
            push(st, ch, top);
        }
        else if (ch == '(')
        {
            while (*top != -1 && st[*top] != ')')
            {
                result[k++] = pop(st, top);
            }

            if (*top != -1)
            {
                pop(st, top);
            }
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            while (*top != -1 && priority(st[*top]) > priority(ch))
            {
                result[k++] = pop(st, top);
            }

            push(st, ch, top);
        }
        else
        {
            result[k++] = ch;
        }
    }

    while (*top != -1)
    {
        result[k++] = pop(st, top);
    }

    result[k] = '\0';

    for (i = k - 1; i >= 0; i--)
    {
        printf("%c", result[i]);
    }

    printf("\n");
}
