#include <stdio.h>
#include <stdlib.h>

// Structure for a Matrix Node
struct Node {
    int data;
    struct Node *right;
    struct Node *down;
};

// Global pointer to point to the top-left corner of the matrix
struct Node *head = NULL;

// Function to Create a Multi-Linked Matrix
void createMatrix(int rows, int cols) {
    /* ALL VARIABLE DECLARATIONS MUST BE AT THE TOP */
    int i, j, value;
    struct Node *rowHead[100];
    struct Node *prevCol;
    struct Node *newNode;

    for (i = 0; i < rows; i++) {
        prevCol = NULL; // Tracks the previous node in the same row

        for (j = 0; j < cols; j++) {
            printf("Enter element for Matrix[%d][%d]: ", i, j);
            scanf("%d", &value);

            // Allocate memory for the new node
            newNode = (struct Node *)malloc(sizeof(struct Node));
            newNode->data = value;
            newNode->right = NULL;
            newNode->down = NULL;

            // Save the head pointer for the very first element (0,0)
            if (i == 0 && j == 0) {
                head = newNode;
            }

            // Connect horizontally (Right pointer)
            if (prevCol != NULL) {
                prevCol->right = newNode;
            }
            prevCol = newNode;

            // Connect vertically (Down pointer)
            if (i > 0) {
                rowHead[j]->down = newNode;
            }

            // Update rowHead array for the next row's vertical connection
            rowHead[j] = newNode;
        }
    }
    printf("\nMatrix created successfully!\n");
}

// Function to Display the Multi-Linked Matrix
void displayMatrix() {
    /* ALL VARIABLE DECLARATIONS MUST BE AT THE TOP */
    struct Node *rowPtr;
    struct Node *colPtr;

    if (head == NULL) {
        printf("\nMatrix is empty! Please create it first.\n");
        return;
    }

    rowPtr = head; // Start from top-left corner

    printf("\n--- Matrix Display ---\n");
    while (rowPtr != NULL) {
        colPtr = rowPtr;
        while (colPtr != NULL) {
            printf("%d\t", colPtr->data);
            colPtr = colPtr->right; // Traverse horizontally
        }
        printf("\n");
        rowPtr = rowPtr->down; // Traverse vertically
    }
}

// Main Menu Driven Program
int main() {
    int choice, rows, cols;

    while (1) {
        printf("\n=========================");
        printf("\n*** MATRIX MENU ***");
        printf("\n1. Create Matrix");
        printf("\n2. Display Matrix");
        printf("\n3. Exit");
        printf("\n=========================");
        printf("\nEnter your choice (1-3): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter number of rows: ");
                scanf("%d", &rows);
                printf("Enter number of columns: ");
                scanf("%d", &cols);
                createMatrix(rows, cols);
                break;

            case 2:
                displayMatrix();
                break;

            case 3:
                printf("\nExiting program... Goodbye!\n");
                exit(0);

            default:
                printf("\nInvalid choice! Please enter 1, 2, or 3.\n");
        }
    }

    return 0;
}