#include <stdio.h>
#define SIZE 10

int hash[SIZE] = {0};

void allocate()
{
    int key, pos;
    printf("Enter key: ");
    scanf("%d", &key);

    pos = key % SIZE;

    while(hash[pos] != 0)
        pos = (pos + 1) % SIZE;

    hash[pos] = key;
    printf("Allocated at position %d\n", pos);
}

void deallocate()
{
    int key, i;
    printf("Enter key to delete: ");
    scanf("%d", &key);

    for(i = 0; i < SIZE; i++)
        if(hash[i] == key)
        {
            hash[i] = 0;
            printf("Deallocated successfully\n");
            return;
        }

    printf("Key not found\n");
}

int main()
{
    int ch;
    do {
        printf("\n1. Allocation\n2. Deallocation\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1: allocate(); break;
            case 2: deallocate(); break;
            case 3: break;
            default: printf("Invalid choice\n");
        }
    } while(ch != 3);

    return 0;
}