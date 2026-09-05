#include <stdio.h>

// Function to create Max Heap
void heapify(int a[], int n, int i)
{
    int largest, left, right, temp;

    // Assume parent is largest
    largest = i;

    // Find left child
    left = 2 * i + 1;

    // Find right child
    right = 2 * i + 2;


    // Check if left child is larger
    if(left < n && a[left] > a[largest])
        largest = left;


    // Check if right child is larger
    if(right < n && a[right] > a[largest])
        largest = right;


    // If child is larger than parent
    if(largest != i)
    {
        // Swap parent and child
        temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;

        // Heapify again
        heapify(a, n, largest);
    }
}


// Function to perform Heap Sort
void heapSort(int a[], int n)
{
    int i, temp;

    // Build Max Heap
    // Start from last non-leaf node
    for(i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);


    // Sort the array
    // Move largest element to the end
    for(i = n - 1; i > 0; i--)
    {
        // Swap first and last element
        temp = a[0];
        a[0] = a[i];
        a[i] = temp;

        // Heapify the remaining elements
        heapify(a, i, 0);
    }
}


int main()
{
    int a[50], n, i;

    // Enter number of elements
    printf("Enter number of elements: ");
    scanf("%d", &n);

    // Enter array elements
    printf("Enter elements: ");

    // Read elements
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    // Call Heap Sort
    heapSort(a, n);

    // Print sorted elements
    printf("Sorted elements: ");

    // Display array
    for(i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}