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
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];
	
    for (i = 0; i < n1; i++)
	{
        L[i] = arr[l + i];
	}
    for (j = 0; j < n2; j++)
	{
        R[j] = arr[m + 1 + j];
	}
	
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) 
	{
        if (L[i] <= R[j]) 
		{
            arr[k] = L[i];
            i++;
        }
        else 
		{
			arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) 
	{
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) 
	{
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
	{
		int m = l + (r - l) / 2;
		
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
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
	int arr [] = {};
	int elements= 0;
	elements= ReadFileIntoarray(argc,argv,&AP);

	clock_t start, end, mstart,mend;

	#ifdef PRINTARRAY
	printf("\n");
	PrintArray(AP,elements);
	#endif

	mstart = clock();
	mergeSort(AP,0,elements-1);
	mend = clock();

	#ifdef PRINTARRAY
	printf("\n");
	PrintArray(AP,elements);
	#endif

	free(AP);
	elements= ReadFileIntoarray(argc,argv,&AP);
	
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
	free(AP);

	printf("\nproceed %d records",elements);
	printf("\ninsertion Sort = %ld Tics",end-start);

	printf("\nMerge sort = %ld tics",mend-mstart);

	return 0; 
} 
