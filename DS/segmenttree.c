#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int sum;
    struct Node *left;
    struct Node *right;
};

struct Node* createNode()
{
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    newNode->sum = 0;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void build(struct Node *node, int a[], int start, int end)
{
    int mid;

    if (start == end)
    {
        node->sum = a[start];
        return;
    }

    mid = (start + end) / 2;

    node->left = createNode();
    node->right = createNode();

    build(node->left, a, start, mid);
    build(node->right, a, mid + 1, end);

    node->sum = node->left->sum + node->right->sum;
}

void freeTree(struct Node *node)
{
    if (node != NULL)
    {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

void display(struct Node *node, int start, int end)
{
    int mid;

    if (start == end)
    {
        printf("%d ", node->sum);
        return;
    }

    mid = (start + end) / 2;

    display(node->left, start, mid);
    display(node->right, mid + 1, end);
}

int rangeSum(struct Node *node, int start, int end,
             int l, int r)
{
    int mid;

    if (r < start || end < l)
        return 0;

    if (l <= start && end <= r)
        return node->sum;

    mid = (start + end) / 2;

    return rangeSum(node->left, start, mid, l, r)
         + rangeSum(node->right, mid + 1, end, l, r);
}


int main()
{
    int a[100];
    int n = 0, i, choice, pos, value, l, r;
    struct Node *root = NULL;

    do
    {
        printf("\n--- SEGMENT TREE MENU ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Range Sum\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                if (n == 100)
                {
                    printf("Array is full\n");
                    break;
                }

                printf("Enter value: ");
                scanf("%d", &value);

                freeTree(root);

                a[n] = value;
                n++;

                root = createNode();
                build(root, a, 0, n - 1);

                printf("Value inserted successfully\n");
                break;

            case 2:
                if (n == 0)
                {
                    printf("Tree is empty\n");
                    break;
                }

                printf("Enter index to delete (0 to %d): ", n - 1);
                scanf("%d", &pos);

                if (pos < 0 || pos >= n)
                {
                    printf("Invalid index\n");
                    break;
                }

                freeTree(root);

                for (i = pos; i < n - 1; i++)
                    a[i] = a[i + 1];

                n--;

                if (n > 0)
                {
                    root = createNode();
                    build(root, a, 0, n - 1);
                }
                else
                {
                    root = NULL;
                }

                printf("Value deleted successfully\n");
                break;

            case 3:
                if (n == 0)
                {
                    printf("Tree is empty\n");
                }
                else
                {
                    printf("Array elements: ");
                    display(root, 0, n - 1);
                    printf("\nTotal Sum: %d\n", root->sum);
                }
                break;

            case 4:
                if (n == 0)
                {
                    printf("Tree is empty\n");
                    break;
                }

                printf("Enter left and right index: ");
                scanf("%d %d", &l, &r);

                if (l < 0 || r >= n || l > r)
                    printf("Invalid range\n");
                else
                    printf("Range Sum = %d\n",
                           rangeSum(root, 0, n - 1, l, r));
                break;

            case 5:
                printf("Exiting program\n");
                break;

            default:
                printf("Invalid choice\n");
        }

    } while (choice != 5);

    freeTree(root);
    return 0;
}
