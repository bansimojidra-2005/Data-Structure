
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

struct node* insert(struct node *root, int x) {
    struct node *temp, *p = root;

    temp = (struct node*)malloc(sizeof(struct node));
    temp->data = x;
    temp->left = temp->right = NULL;

    if (root == NULL)
        return temp;

    while (p != NULL) {
        if (x < p->data) {
            if (p->left == NULL) {
                p->left = temp;
                break;
            }
            p = p->left;
        } else {
            if (p->right == NULL) {
                p->right = temp;
                break;
            }
            p = p->right;
        }
    }
    return root;
}

void display(struct node *root) {
    struct node *stack[100];
    int top = -1;
    struct node *p = root;

    while (p != NULL || top != -1) {
        while (p != NULL) {
            stack[++top] = p;
            p = p->left;
        }
        p = stack[top--];
        printf("%d ", p->data);
        p = p->right;
    }
}

struct node* deleteNode(struct node *root, int x) {
    struct node *p = root, *parent = NULL, *temp;

    while (p != NULL && p->data != x) {
        parent = p;
        if (x < p->data)
            p = p->left;
        else
            p = p->right;
    }

    if (p == NULL) {
        printf("Node not found!");
        return root;
    }

    if (p->left != NULL && p->right != NULL) {
        temp = p->right;
        while (temp->left != NULL)
            temp = temp->left;
        p->data = temp->data;
        return deleteNode(p->right, temp->data) == NULL
               ? root : root;
    }

    temp = (p->left != NULL) ? p->left : p->right;

    if (parent == NULL)
        root = temp;
    else if (parent->left == p)
        parent->left = temp;
    else
        parent->right = temp;

    free(p);
    return root;
}

int main() {
    struct node *root = NULL;
    int ch, x;

    do {
        printf("\n\n1. Insert");
        printf("\n2. Display");
        printf("\n3. Delete");
        printf("\n4. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Enter integer: ");
                scanf("%d", &x);
                root = insert(root, x);
                break;
            case 2:
                printf("Inorder Display: ");
                display(root);
                break;
            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &x);
                root = deleteNode(root, x);
                break;
            case 4:
                printf("Exiting...");
                break;
            default:
                printf("Invalid choice!");
        }
    } while (ch != 4);

    return 0;
}
