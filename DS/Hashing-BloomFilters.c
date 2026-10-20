#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20 // Bit Array 

// Bloom Filter 
struct BloomFilter {
    int *bitArray;
    int size;
};

// Global Pointer
struct BloomFilter *filter = NULL;

// 1st Hash Function (Simple Sum Hash)
int hash1(char *str, int size) {
    int sum = 0, i;
    for (i = 0; str[i] != '\0'; i++) {
        sum += str[i];
    }
    return sum % size;
}

// 2nd Hash Function (Weighted Hash)
int hash2(char *str, int size) {
    int sum = 0, i;
    for (i = 0; str[i] != '\0'; i++) {
        sum = sum + (str[i] * (i + 1));
    }
    return sum % size;
}

// 1. ALLOCATION (Bloom Filter)
void allocateBloomFilter() {
    int i;
    
    
    if (filter != NULL) {
        printf("\nBloom Filter is already allocated!\n");
        return;
    }

    // Dynamic Memory Allocation using malloc
    filter = (struct BloomFilter *)malloc(sizeof(struct BloomFilter));
    filter->size = SIZE;
    filter->bitArray = (int *)malloc(SIZE * sizeof(int));

    
    for (i = 0; i < SIZE; i++) {
        filter->bitArray[i] = 0;
    }

    printf("\nBloom Filter Memory Allocated Successfully! (Size: %d)\n", SIZE);
}

// 2. DEALLOCATION 
void deallocateBloomFilter() {
    if (filter == NULL) {
        printf("\nNo Bloom Filter to deallocate!\n");
        return;
    }

    
    free(filter->bitArray);
    
    free(filter);
    
    filter = NULL; // Pointer Reset
    printf("\nBloom Filter Deallocated Successfully!\n");
}

// Bloom Filter 
void insertElement(char *str) {
    int index1, index2;

    if (filter == NULL) {
        printf("\nPlease Allocate Bloom Filter first (Option 1)!\n");
        return;
    }

    
    index1 = hash1(str, filter->size);
    index2 = hash2(str, filter->size);

    // Bit Array 
    filter->bitArray[index1] = 1;
    filter->bitArray[index2] = 1;

    printf("\n'%s' inserted! (Bits set at Index %d and %d)\n", str, index1, index2);
}

// Bloom Filter 
void searchElement(char *str) {
    int index1, index2;

    if (filter == NULL) {
        printf("\nPlease Allocate Bloom Filter first (Option 1)!\n");
        return;
    }

    index1 = hash1(str, filter->size);
    index2 = hash2(str, filter->size);

    // ?? ???? ???????? ?? 1 ???
    if (filter->bitArray[index1] == 1 && filter->bitArray[index2] == 1) {
        printf("\n'%s' is PROBABLY PRESENT in Bloom Filter.\n", str);
    } else {
        printf("\n'%s' is DEFINITELY NOT PRESENT in Bloom Filter.\n", str);
    }
}


void displayBitArray() {
    int i;
    if (filter == NULL) {
        printf("\nBloom Filter is not allocated!\n");
        return;
    }

    printf("\n--- Current Bit Array ---\n[ ");
    for (i = 0; i < filter->size; i++) {
        printf("%d ", filter->bitArray[i]);
    }
    printf("]\n");
}

// Main Menu
int main() {
    int choice;
    char item[50];

    while (1) {
        printf("\n==================================");
        printf("\n*** BLOOM FILTER MENU ***");
        printf("\n1. Allocation (Create Bloom Filter)");
        printf("\n2. Insert Item");
        printf("\n3. Search Item");
        printf("\n4. Display Bit Array");
        printf("\n5. Deallocation (Free Memory)");
        printf("\n6. Exit");
        printf("\n==================================");
        printf("\nEnter choice (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                allocateBloomFilter();
                break;

            case 2:
                printf("\nEnter string to insert: ");
                scanf("%s", item);
                insertElement(item);
                break;

            case 3:
                printf("\nEnter string to search: ");
                scanf("%s", item);
                searchElement(item);
                break;

            case 4:
                displayBitArray();
                break;

            case 5:
                deallocateBloomFilter();
                break;

            case 6:
                if (filter != NULL) {
                    deallocateBloomFilter(); // Exit 
                }
                printf("\nExiting program... Goodbye!\n");
                exit(0);

            default:
                printf("\nInvalid Choice! Enter between 1-6.\n");
        }
    }

    return 0;
}