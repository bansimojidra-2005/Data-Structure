
#include <stdio.h>

int adj[10][10], visited[10], n;

void create()
{
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &adj[i][j]);

    printf("Graph created successfully!\n");
}

void BFS(int start)
{
    int queue[10], front = 0, rear = 0;
    int i, v;

    for(i = 0; i < n; i++)
        visited[i] = 0;

    queue[rear++] = start;
    visited[start] = 1;

    printf("BFS: ");

    while(front < rear)
    {
        v = queue[front++];
        printf("%d ", v);

        for(i = 0; i < n; i++)
        {
            if(adj[v][i] == 1 && !visited[i])
            {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

void DFS(int v)
{
    int i;

    visited[v] = 1;
    printf("%d ", v);

    for(i = 0; i < n; i++)
    {
        if(adj[v][i] == 1 && !visited[i])
            DFS(i);
    }
}

int main()
{
    int ch, start, i;

    do
    {
        printf("\n1. Create");
        printf("\n2. BFS");
        printf("\n3. DFS");
        printf("\n4. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &ch);

        switch(ch)
        {
            case 1:
                create();
                break;

            case 2:
                printf("Enter starting vertex (0 to %d): ", n-1);
                scanf("%d", &start);
                BFS(start);
                break;

            case 3:
                for(i = 0; i < n; i++)
                    visited[i] = 0;

                printf("Enter starting vertex (0 to %d): ", n-1);
                scanf("%d", &start);
                printf("DFS: ");
                DFS(start);
                printf("\n");
                break;

            case 4:
                printf("Exiting...");
                break;

            default:
                printf("Invalid choice!");
        }
    } while(ch != 4);

    return 0;
}
