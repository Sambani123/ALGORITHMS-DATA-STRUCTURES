/*Samuel Ambani 1001694453 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHTABLESIZE 10
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

int MyHashFunction(char Champions[])
{
	int total;
	int i;

	for (i = 0; i < strlen(Champions); i++)
	{
    	total +=Champions[i];
	}

	return total % HASHTABLESIZE;
}

int main(void)
{
	char HashValue[20];
	printf("Enter value ");
	scanf("%s", HashValue);
	printf("The hash value for %s is %d\n", HashValue, MyHashFunction(HashValue));
	return 0;
}


