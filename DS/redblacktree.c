
#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

struct Node {
    int data, color;
    struct Node *left, *right, *parent;
};

struct Node *root = NULL;

struct Node* createNode(int data) {
    struct Node *n = malloc(sizeof(struct Node));

    n->data = data;
    n->color = RED;
    n->left = n->right = n->parent = NULL;

    return n;
}

void leftRotate(struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rightRotate(struct Node *y) {
    struct Node *x = y->left;
    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}

void fixInsert(struct Node *z) {
    while (z != root && z->parent->color == RED) {
        struct Node *p = z->parent;
        struct Node *g = p->parent;

        if (p == g->left) {
            struct Node *u = g->right;

            if (u != NULL && u->color == RED) {
                p->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                z = g;
            } else {
                if (z == p->right) {
                    z = p;
                    leftRotate(z);
                    p = z->parent;
                    g = p->parent;
                }

                p->color = BLACK;
                g->color = RED;
                rightRotate(g);
            }
        } else {
            struct Node *u = g->left;

            if (u != NULL && u->color == RED) {
                p->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                z = g;
            } else {
                if (z == p->left) {
                    z = p;
                    rightRotate(z);
                    p = z->parent;
                    g = p->parent;
                }

                p->color = BLACK;
                g->color = RED;
                leftRotate(g);
            }
        }
    }

    root->color = BLACK;
}

void insert(int data) {
    struct Node *z = createNode(data);
    struct Node *p = NULL;
    struct Node *x = root;

    while (x != NULL) {
        p = x;

        if (data < x->data)
            x = x->left;
        else if (data > x->data)
            x = x->right;
        else {
            free(z);
            printf("Duplicate value not allowed\n");
            return;
        }
    }

    z->parent = p;

    if (p == NULL)
        root = z;
    else if (data < p->data)
        p->left = z;
    else
        p->right = z;

    fixInsert(z);
}

void inorder(struct Node *x) {
    if (x != NULL) {
        inorder(x->left);
        printf("%d(%s) ", x->data,
               x->color == RED ? "R" : "B");
        inorder(x->right);
    }
}

int main() {
    int choice, data;

    while (1) {
        printf("\n1. Insert\n2. Display\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &data);
                insert(data);
                break;

            case 2:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;

            case 3:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}
