/*Queue*/
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define max 5

int Q[max];
void main()
{
	int choice,ele,Remove;
	int *front;
	int *rear;
	
	void Q_Insert(int *,int *,int ele);
	int Q_Delete(int *,int *);
	void Q_Display(int *,int *);

	front=(int *)malloc(sizeof(int));
	rear=(int *)malloc(sizeof(int));

	*front=-1;
	*rear=-1;
	  
	while(choice!=4)
	{
		  printf("1 . Insert \n");
		printf("2 . Delete \n");
		printf("3 . Display \n");
		printf("4 . Exit\n");
		

		printf("Enter Your Choice: ");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:
					printf("Enter Your Element: ");
					scanf("%d",&ele);
					Q_Insert(front,rear,ele);
					break;
				   
			case 2:
					if((*rear)==-1 && (*front)==-1)
					{
							printf(" Queue is Empty \n");
					}
					else
					{
						Remove=Q_Delete(front,rear);
						printf("Removed Value is %d \n",Remove);	
					}
					break;
				   
			case 3:
					Q_Display(front,rear);
					break;
				   
			case 4:
				exit(0);
				break;
			
		
		}
	//	printf("Enter Your Choice: ");
	//	scanf("%d",&choice);

	}
}
void Q_Insert(int *front,int *rear,int ele)
{
	if((*front)==-1 && (*rear)==-1)
	{
		(*front)=(*rear)=0;
		Q[(*rear)]=ele;
	}
	else
	{
		if((*rear)==max-1 )
		{
			printf(" Queue Is Full \n");
		}
		else
		{
			(*rear)=(*rear)+1;
			Q[(*rear)]=ele;
		}
		
	}
}
int Q_Delete(int *front,int *rear)
{	int Remove;
	if((*rear)==-1 && (*front)==-1)
	{
		printf(" Queue is Empty \n");
	}
	else
	{
		if((*front)==(*rear))
		{
			Remove=Q[(*front)];
			(*front)=(*rear)=-1;
		}
		else
		{
			Remove=Q[(*front)];
			(*front)=(*front)+1;	
		}
	}
	return Remove;
}
void Q_Display(int *front,int *rear)
{	int i;
		for(i=(*front);i<=(*rear);i++)
		{
			printf("%d \n",Q[i]);
		}
}