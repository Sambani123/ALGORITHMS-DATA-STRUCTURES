// Coding Assignment 6 - Samuel Ambani - 1001694453

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
 
#define HASHTABLESIZE 30

 
/* Node for storing information */
typedef struct Champions 
{
    char *name;
    float winrate;
    float banrate;
    char gender;
    char *role;
    int picknumber;
    struct Champions *next_ptr;
}
CHAMPIONS;

 
/* This function creates an index corresponding to the input key */
int CalculateHashIndex(char *key)
{
	int HashIndex = 0;
    int i;
	
	for ( i = 0; i < strlen(key); i++)
	{
		HashIndex += key[i];
	}
	
	return HashIndex %= HASHTABLESIZE; 
}

void AddNode(CHAMPIONS *NewNode, CHAMPIONS *Pokedex[])
{
	int HashIndex = CalculateHashIndex(NewNode->name);
	
	/* a linked list does not exist for this cell of the array */
	if (Pokedex[HashIndex] == NULL) 
	{
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
		Pokedex[HashIndex] = NewNode;
	}
	else   /* A Linked List is present at given index of Hash Table */ 
	{
		CHAMPIONS *TempPtr = Pokedex[HashIndex];
	
		/* Traverse linked list */
		while (TempPtr->next_ptr != NULL) 
		{
			TempPtr = TempPtr->next_ptr;
		}
		TempPtr->next_ptr = NewNode;
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
	}
}

void FreeDynamicMemory(CHAMPIONS *Champion[])
{
	CHAMPIONS *TempPtr = NULL, *NextPtr = NULL;
    int i;
	
	for ( i = 0; i < HASHTABLESIZE; i++)
	{
		TempPtr = Champion[i];
 
		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL) 
			{
				free(TempPtr->name);
				//free(TempPtr->gender);
				free(TempPtr->role);
				NextPtr = TempPtr->next_ptr;
				free(TempPtr);
				TempPtr = NextPtr;
			}	
		}
	}
}


/* Remove an element from Hash Table */ 
int DeleteNode(CHAMPIONS *Champions[])
{
	char LookupName[100] = {};
	int result = 0;
	
	printf("Enter the name of the Champion to delete from the Pokedex ");
	scanf("%s", LookupName);

	int HashIndex = CalculateHashIndex(LookupName);

	/* Get linked list at key in array */
	CHAMPIONS *TempPtr = Champions[HashIndex];
	CHAMPIONS *PrevPtr = NULL;
 
	/* This array index does not have a linked list; therefore, no keys */
	if (TempPtr == NULL) 
	{
		printf("\n\nPokemon %s does not exist in the Pokedex\n\n", LookupName);
		result = 0;
	}
	else 
	{
		while (TempPtr != NULL) 
		{
			if (strcmp(TempPtr->name, LookupName) == 0)
			{
				/* If the node being deleted is the head node */
				if (TempPtr == Champions[HashIndex])
				{
					/* The node the head was pointing at is now the head */
					Champions[HashIndex] = TempPtr->next_ptr;
					printf("\nPokemon %s has been deleted from the Pokedex\n\n", TempPtr->name);
					free(TempPtr);
					TempPtr = NULL;
				}
				/* Found node to be deleted - node is not the head */
				else
				{
					PrevPtr->next_ptr = TempPtr->next_ptr;
					printf("\nPokemon %s has been deleted from the Pokedex\n\n", TempPtr->name);
					free(TempPtr);
					TempPtr = NULL;
				}
				result = 1;
			}
			/* this is not the node that needs to be deleted but save */
			/* its info and move to the next node in the linked list  */
			else
			{
				PrevPtr = TempPtr;
				TempPtr = TempPtr->next_ptr;
			}
		}
		if (result == 0)
		{
			printf("\n\nPokemon %s does not exist in the Pokedex\n\n", LookupName);
		}
	}
	return result;
}

/* display the contents of the Hash Table */
void DisplayHashTable(CHAMPIONS *Champions[])
{
	int i;
	CHAMPIONS *TempPtr = NULL;
	
	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = Champions[i];

		printf("\nChampion[%d]-", i);
		
		if (TempPtr != NULL) 
        {
			while (TempPtr != NULL)
			{
				printf("%s|", TempPtr->name);
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}

void ShowByLetter(CHAMPIONS *Champions[])
{
	int i;
	CHAMPIONS *TempPtr = NULL;
	char LookupLetter = 'A';

	printf("\n\nEnter a letter of the alphabet ");
	scanf(" %c", &LookupLetter);
	LookupLetter = toupper(LookupLetter);

	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = Champions[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (toupper(TempPtr->name[0]) == LookupLetter)
				{
					printf("%s\n", TempPtr->name);
				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}

void ShowByName(CHAMPIONS *Champions[])
{
	CHAMPIONS *TempPtr = NULL;
	char winrate[10] = {}; // winrate  // height 
	char banrate[10] = {};  // loserate //wieght 
	//char inches[10] = {};
	char LookupName[100] = {};
	int FoundIt = 0;
	
	printf("\n\nEnter Champion's name ");
	scanf("%s", LookupName);
	
	#if TIMING
	clock_t start, end;
	start = clock();
	#endif
    int i;
	for ( i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = Champions[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (strcmp(TempPtr->name, LookupName) == 0)
				{
					#if TIMING
					end = clock();
					printf("\n\nSearch took %ld tics\n\n", end-start);
					#endif

					FoundIt = 1;
					printf("\n\n%s\n", TempPtr->name);
					
					printf("Winrate\t\t");
					sprintf(winrate, "%.2f", TempPtr->winrate);
                    int i;
					for ( i = 0; i < strlen(winrate); i++)
					{
						if (winrate[i] == '.')
						{
							printf("\' ");
						}
						else
						{
							printf("%c", winrate[i]);
						}
					}
					printf("\"\n");
					printf("loserate\t\t%.1f \n", TempPtr->banrate);
					if (TempPtr->gender == 'M')
						printf("Gender\t\tM F\n");
					else if (TempPtr->gender == 'W')
						printf("Gender\t\tW\n");
					else
						printf("Gender\t\t%c\n", TempPtr->gender);
					printf("Role\t%s\n", TempPtr->role);
					printf("Ranked number\t%d\n", TempPtr->picknumber);
					

				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
	
	if (FoundIt == 0)
		printf("\n\nChampion %s not found in Champions\n\n", LookupName);
}

void AddNewPokemon(CHAMPIONS *Champions[])
{
	int HashIndex = 0;
	CHAMPIONS *NewNode;
	char TempBuffer[100] = {};

	NewNode = malloc(sizeof(CHAMPIONS));
	NewNode->next_ptr = NULL;

	printf("\n\nEnter new Champion's name ");
	scanf("%s", TempBuffer);
	NewNode->name = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->name, TempBuffer);

	printf("\n\nEnter %s's Winrate as decimal ", NewNode->name);
	scanf("%f", &(NewNode->winrate));
	
	printf("\n\nEnter %s's loserate as decimal ", NewNode->name);
	scanf("%f", &(NewNode->banrate));
	
	printf("\n\nEnter %s's possible gender (M/F) ", NewNode->name);
	scanf(" %c", &(NewNode->gender));
	NewNode->gender = toupper(NewNode->gender);
	
	// Extra fgets to clear stdin
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);
	
	printf("\n\nEnter %s's Role ", NewNode->name);
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin); 
	TempBuffer[strlen(TempBuffer)-1] = '\0';
	NewNode->role = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->role, TempBuffer);

	printf("\n\nEnter %s's Ranked Number ", NewNode->name);
	scanf("%d", &(NewNode->picknumber));

	AddNode(NewNode, Champions);
}

int ReadFileIntoHashTable(int argc, char *argv[], CHAMPIONS *Champions[])
{
	FILE *FH = NULL;
	char FileLine[100] = {};
	char *token = NULL;
	int counter = 0;
	int HashIndex = 0;
	CHAMPIONS *NewNode;

	if (argc > 1)
	{
		FH = fopen(argv[1], "r");

		if (FH == NULL)
		{
			perror("Exiting ");
			exit(0);
		}
		
		while (fgets(FileLine, sizeof(FileLine)-1, FH))
		{
			token = strtok(FileLine, "|");

			NewNode = malloc(sizeof(CHAMPIONS));
			NewNode->next_ptr = NULL;
			
			NewNode->name = malloc(strlen(token)*sizeof(char)+1);
			strcpy(NewNode->name, token);

			token = strtok(NULL, "|");
			NewNode->winrate = atof(token);
			
			token = strtok(NULL, "|");
			NewNode->banrate = atof(token);
			
			token = strtok(NULL, "|");
			NewNode->gender = *token;

			token = strtok(NULL, "|");
			NewNode->role = malloc(strlen(token)*sizeof(char)+1);
			strcpy(NewNode->role, token);
			
			token = strtok(NULL, "|");
			NewNode->picknumber = atoi(token);

			AddNode(NewNode, Champions);

			counter++;
		}

	}
	else
	{
		printf("File must be provided on command line...exiting\n");
		exit(0);
	}
	
	fclose(FH);
	
	return counter;
}

int main(int argc, char *argv[]) 
{
	int MenuChoice = 0;
	int counter = 0;
	CHAMPIONS *Champions[HASHTABLESIZE] = {};

	enum Menu {SHOWBYLETTER=1, SHOWBYNAME, COUNT, DISPLAY, ADD, DELETE, EXIT};
 
	counter = ReadFileIntoHashTable(argc, argv, Champions);
 
	do
	{
		printf("\n\nPokedex Menu\n\n"
			   "1. Show all Champions in rift for a given letter\n"
			   "2. Look up Champions by name\n"
			   "3. How many Pokemon are in the Pokedex?\n"
			   "4. Display the Champions\n"
			   "5. Add a new Champion\n"
			   "6. Delete a Champions from the rift\n"
			   "7. Exit\n\n"
			   "Enter menu choice ");
	
		scanf("%d", &MenuChoice);
		printf("\n\n");

		switch (MenuChoice)
		{	
			case SHOWBYLETTER:
				ShowByLetter(Champions);
				break;
			case SHOWBYNAME:
				ShowByName(Champions);
				break;
			case COUNT:
				printf("Your league of legends count %d Champions\n", counter); 
				break;
 			case DISPLAY:
				DisplayHashTable(Champions);
				break;
			case ADD:
				AddNewPokemon(Champions);
				counter++;
				break;
			case DELETE:
				if (DeleteNode(Champions))
				{
					counter--;
				}
				break;
			case EXIT:
				break;
			default : 
				printf("Invalid menu choice\n\n"); 
		}
	}
	while (MenuChoice != EXIT);
	
	FreeDynamicMemory(Champions);

	return 0;
}	
