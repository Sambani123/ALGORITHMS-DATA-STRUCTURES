/* Coding Assignment 4 */
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
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
int partition (int arr[], int low, int high)
{
	#if QSM
	int middle = (high+low)/2;
	swap(&arr[middle], &arr[high]);
	#elif QSRND
	int random = (rand() % (high-low+1) + low);
	swap(&arr[random], &arr[high]);
	#endif
	int pivot = arr[high];
	
    int i = (low - 1);
	 int j;	
    for ( j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap (&arr[i + 1], &arr[high]);
    return (i + 1);
}
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
		
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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
		if (argc != 3)
		{
			printf("Number of Runs now specified on command line... defaulting to 10\n");
		}

		printf("File must be provided on command line...exiting \n");
		exit(0);
	}
	fclose(fp);
}


int main(int argc , char* argv[]) 
{ 
	int *AP = NULL;
	int arr [] = {};
	int elements= 0;
	//elements= ReadFileIntoarray(argc,argv,&AP);

	clock_t start, end, mstart,mend;
	int loop;
	long int sum = 0;
	long int average = 0;
	int runcount = 1;
	int j ;
	if (argc < 3)
	{
		printf("Number of Runs now specified on command line... deafaulting to 10\n");
		loop = 10;
	}
	else
	{
		loop = atoi(argv[2]);
	}
	
	for(j = 0; j < loop; j++)
	{ 
		elements= ReadFileIntoarray(argc,argv,&AP);
		#ifdef PRINTARRAY
		printf("Given array is \n");
		PrintArray(AP, elements);
		#endif
			
		start = clock();
		quickSort(AP, 0, elements - 1);
		end = clock();
		printf("Run %d complete: %ld tics\n", runcount, end-start);
		sum += end-start;
			
		#ifdef PRINTARRAY
		printf("\nQuick Sort Array Sorted is \n");
		PrintArray(AP, elements);
		#endif
		runcount++;
		free(AP);
			
	}
	average = sum / loop;
	printf("Average run time for %d is %ld\n", loop, average);	

	printf("\nproceed %d records\n",elements);
	

	return 0; 
} 
