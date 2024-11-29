/* Coding Assignment 1 */
// Samuel Ambani 1001694453
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>





void PrintArray (int ArrayToPrint [], int SizeAp)
{
	int i ;

	for ( i = 0; i < SizeAp; i++)
		printf("%d\n",ArrayToPrint[i]);
	
}


void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) 
	{
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) 
		{
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
int ReadFileIntoarray(int argc,  char *argv[], int **AP)
{
	char Filename[100];
	int Count= 0;
	int num;
	int sum;
	FILE *fp;
	int i = 0;
	
	if(argv[1]!= NULL)
	{
		strcpy(Filename,argv[1]);
		fp = fopen(Filename,"r");

		while (fgets(Filename,sizeof(Filename),fp))
		{
			Count++;
		}

		fseek(fp,0,0);
		*AP = malloc(Count*sizeof(int));

		while (fgets(Filename,sizeof(Filename),fp))
		{
			
			(*AP)[i] = atoi(Filename);
			i++;
		}
		return i;
	}
	else
	{
		printf("File must be provided on command line...exiting \n");
		exit(0);
	}
	fclose(fp);
}


int main(int argc , char* argv[]) 
{ 
	int *AP = NULL;
	int elements= 0;
	elements= ReadFileIntoarray(argc,argv,&AP);

	clock_t start, end;

	#ifdef PRINTARRAY
	printf("\n");
	PrintArray(AP,elements);
	#endif

	start = clock();
	insertionSort(AP,elements);
	end = clock();

	#ifdef PRINTARRAY
	printf("\n");
	PrintArray(AP,elements);
	#endif
	printf("\nproceed %d records",elements);
	printf("\ninsertion Sort = %ld Tics",end-start);
	free(AP);

		return 0; 
} 
