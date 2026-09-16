#include<stdio.h>
#define size 5

int hash(int key)
{
	return key % size;
}
void addServer(int server)
{
	printf("Server %d added at position %d\n", server,hash(server));
}
void findServer(int key)
{
	int position = hash(key);
	printf("Key %d is mapped to position %d\n",key,position);
}
int main()
{
	int server, key, choice;
	printf("Consistent Hashing\n");
	while(1)
	{
		printf("\n1.Add Server \n2. Find Server \n3.Exit");

		printf("\nEnter your choice:");
		scanf("%d",&choice);

		switch(choice)
		{
		case 1:
			printf("Enter Server ID:");
			scanf("%d",&server);
			addServer(server);
			break;
		case 2:
			printf("Enter key:");
			scanf("%d",&key);
			findServer(key);
			break;
		case 3:
			return 0;
		default:
			printf("Invalid choice...");
		}
	}
	return 0;
}