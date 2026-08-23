#include <stdio.h>
#include <stdlib.h>

void enqueue(int *queue, int *priority, int *size, int max);
void dequeue(int *queue, int *priority, int *size);
void display(int *queue, int *priority, int *size);

int main()
{
    int *queue, *priority;
    int size = 0, max, choice;

    printf("Enter size of Priority Queue: ");
    scanf("%d", &max);

    queue = (int *)malloc(max * sizeof(int));
    priority = (int *)malloc(max * sizeof(int));

    if (queue == NULL || priority == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    while (1)
    {
        printf("\n--- PRIORITY QUEUE ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                enqueue(queue, priority, &size, max);
                break;

            case 2:
                dequeue(queue, priority, &size);
                break;

            case 3:
                display(queue, priority, &size);
                break;

            case 4:
                free(queue);
                free(priority);
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}

// Enqueue
void enqueue(int *queue, int *priority, int *size, int max)
{
    int value, p;

    if (*size == max)
    {
        printf("Priority Queue is Full!\n");
        return;
    }

    printf("Enter value: ");
    scanf("%d", &value);

    printf("Enter priority: ");
    scanf("%d", &p);

    queue[*size] = value;
    priority[*size] = p;

    (*size)++;

    printf("%d inserted successfully.\n", value);
}

// Dequeue
void dequeue(int *queue, int *priority, int *size)
{
    int i, pos = 0;

    if (*size == 0)
    {
        printf("Priority Queue is Empty!\n");
        return;
    }

    // Find highest priority
    for (i = 1; i < *size; i++)
    {
        if (priority[i] < priority[pos])
        {
            pos = i;
        }
    }

    printf("%d deleted successfully.\n", queue[pos]);

    // Shift elements
    for (i = pos; i < *size - 1; i++)
    {
        queue[i] = queue[i + 1];
        priority[i] = priority[i + 1];
    }

    (*size)--;
}

// Display
void display(int *queue, int *priority, int *size)
{
    int i;

    if (*size == 0)
    {
        printf("Priority Queue is Empty!\n");
        return;
    }

    printf("\nValue\tPriority\n");

    for (i = 0; i < *size; i++)
    {
        printf("%d\t%d\n", queue[i], priority[i]);
    }
}

