
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

struct node* insert(struct node *root, int x) {
    if (root == NULL) {
        root = (struct node*)malloc(sizeof(struct node));
        root->data = x;
        root->left = root->right = NULL;
    }
    else if (x < root->data)
        root->left = insert(root->left, x);
    else
        root->right = insert(root->right, x);

    return root;
}

void preorder(struct node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(struct node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void postorder(struct node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    struct node *root = NULL;
    int ch, x;

    do {
        printf("\n\n1. Insert");
        printf("\n2. Preorder");
        printf("\n3. Inorder");
        printf("\n4. Postorder");
        printf("\n5. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Enter integer: ");
                scanf("%d", &x);
                root = insert(root, x);
                break;

            case 2:
                printf("Preorder: ");
                preorder(root);
                break;

            case 3:
                printf("Inorder: ");
                inorder(root);
                break;

            case 4:
                printf("Postorder: ");
                postorder(root);
                break;

            case 5:
                printf("Exiting...");
                break;

            default:
                printf("Invalid choice!");
        }
    } while (ch != 5);

    return 0;
}
