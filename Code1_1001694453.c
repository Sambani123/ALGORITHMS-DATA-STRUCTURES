/* Coding Assignment 1 */
// Samuel Ambani 1001694453
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>


typedef struct node
{
	int number;
	struct node *next_ptr;
}
NODE;

void AddNodeToLL(int Number, NODE **LinkedListHead)
{
	NODE *NewNode;
	NewNode = malloc(sizeof(NODE));
	NewNode -> number = Number;
	NewNode ->next_ptr = NULL;

	if (*LinkedListHead == NULL)
	{
		*LinkedListHead = NewNode;
	}
	else
	{
		NODE *Lastnode = *LinkedListHead;
		while (Lastnode ->next_ptr != NULL)
		{
			Lastnode = Lastnode ->next_ptr;

		}
		Lastnode ->next_ptr = NewNode;
	}
	
}

void ReadFileIntoLL(int argc,  char *argv[], NODE **LLH)
{
	char Filename[100];
	strcpy(Filename,argv[1]);
	int Count;
	int num;
	int sum;
	FILE *fp;
	fp = fopen(Filename,"r");
	while (fgets(Filename,sizeof(Filename),fp))
	{
		num = atoi(Filename);
		AddNodeToLL(num,LLH);
		Count++;
		sum += atoi(Filename);
	}
	printf("%d Records were read for a total sum of %d\n",Count,sum);
	fclose(fp);
	
}

void PrintLL(NODE *LLH) 
{ 
	struct node *temp;
	temp = LLH;
	while (temp != NULL)
	{
		printf("\n%p %d %p\n",temp,temp->number,temp->next_ptr);
		temp = temp ->next_ptr;
	}

	
}

void FreeLL(NODE **LLH) 
{ 
	#ifdef PRINT
	NODE *Temp_ptr = *LLH;
	NODE *next_ptr;

	while (Temp_ptr != NULL)
	{
		next_ptr = Temp_ptr -> next_ptr;
		printf("\nFreeing %p %d %p \n",Temp_ptr,Temp_ptr-> number,Temp_ptr->next_ptr);
		free(Temp_ptr);
		Temp_ptr= next_ptr;
	}
	#endif
}

int main(int argc , char* argv[]) 
{ 
	NODE *LLH = NULL;
	clock_t start, end;

	if (argc==2)
	{
			
		start = clock();/* capture the clock in a start time */

		ReadFileIntoLL(argc, argv, &LLH);
		end = clock();/* capture the clock in an end time */

		
		printf("\n%ld tics to write the file into the linked list\n", end-start);

		
		#ifdef PRINT
		start = clock();/* capture the clock in a start time */
		PrintLL(LLH);
		end = clock();
		#endif /* capture the clock in an end time */

		printf("\n%ld tics to print the linked list\n", end-start);
		
		start = clock();/* capture the clock in a start time */
		FreeLL(&LLH);
		end = clock(); /* capture the clock in an end time */
		printf("\n%ld tics to free the linked list\n", end-start);
	}
	else
	{
		printf("File must be provided on command line... exiting\n");
	}
		return 0; 
} 
