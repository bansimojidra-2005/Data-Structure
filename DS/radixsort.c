#include<stdio.h>

void radix(int a[], int value)
{
    int i, k;
    int max = a[0];
    int place = 1;
    int b[100];
    int count[10];

    // Find maximum element
    for(i = 0; i < value; i++)
    {
        if(a[i] > max)
        {
            max = a[i];
        }
    }

    // Radix sort
    while(max / place > 0)
    {
        // Initialize count
        for(i = 0; i < 10; i++)
        {
            count[i] = 0;
        }

        // Count digits
        for(i = 0; i < value; i++)
        {
            count[(a[i] / place) % 10]++;
        }

        // Cumulative count
        for(i = 1; i < 10; i++)
        {
            count[i] = count[i] + count[i - 1];
        }

        // Store elements in b[]
        for(i = value - 1; i >= 0; i--)
        {
            k = (a[i] / place) % 10;
            b[count[k] - 1] = a[i];
            count[k]--;
        }

        // Copy b[] to a[]
        for(i = 0; i < value; i++)
        {
            a[i] = b[i];
        }

        place = place * 10;
    }
}

int main()
{
    int a[100];
    int n, i;

    printf("\nEnter number of elements: ");
    scanf("%d", &n);

    printf("\nEnter elements: ");

    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    radix(a, n);

    printf("\nSorted elements: ");

    for(i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    return 0;
}