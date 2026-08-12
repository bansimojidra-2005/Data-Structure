//circular queue
#include <stdio.h>
#include <stdlib.h>
#define max 5

int CQ[max];


void main()
{
	
	// Function declarations
	void CQ_Insert(int *, int *, int ele);
	int CQ_Delete(int *, int *);
	void CQ_Display(int *, int *);

    int choice, ele, Remove;
    int *front, *rear;

    front = (int *)malloc(sizeof(int));
    rear = (int *)malloc(sizeof(int));

    *front = -1;
    *rear = -1;

    while (1)
    {
        printf("\n1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Exit\n");

        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter Your Element: ");
            scanf("%d", &ele);
            CQ_Insert(front, rear, ele);
            break;

        case 2:
            Remove = CQ_Delete(front, rear);
            if (Remove != -1)
                printf("Removed Value is %d\n", Remove);
            break;

        case 3:
            CQ_Display(front, rear);
            break;

        case 4:
            exit(0);
            break;

        default:
            printf("Invalid Choice\n");
        }
    }
}

void CQ_Insert(int *front, int *rear, int ele)
{
    if ((*front == 0 && *rear == max - 1) || (*rear + 1) % max == *front)
    {
        printf("Circular Queue Is Full\n");
    }
    else
    {
        if (*front == -1 && *rear == -1)
        {
            *front = *rear = 0;
        }
        else
        {
            *rear = (*rear + 1) % max;
        }
        CQ[*rear] = ele;
    }
}

int CQ_Delete(int *front, int *rear)
{
    int Remove;

    if (*front == -1 && *rear == -1)
    {
        printf("Circular Queue is Empty\n");
        return -1;
    }

    Remove = CQ[*front];

    if (*front == *rear)
    {
        *front = *rear = -1;
    }
    else
    {
        *front = (*front ++) % max;
    }

    return Remove;
}

void CQ_Display(int *front, int *rear)
{
    int i;

    if (*front == -1 && *rear == -1)
    {
        printf("Circular Queue is Empty\n");
    }
    else
    {
        printf("Queue elements: ");
        i = *front;
        while (1)
        {
            printf("%d ", CQ[i]);
            if (i == *rear)
                break;
            i = (i + 1) % max;
        }
        printf("\n");
    }
}

