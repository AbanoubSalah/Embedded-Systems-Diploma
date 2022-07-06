#include <stdio.h>
#include <stdlib.h>

#define ARRAY_MAX_LENGTH (100)

int main()
{
	int array[ARRAY_MAX_LENGTH];
	int *arrayPtr = array;
	int arrayLength;
	int idx;

	printf("Input the number of elements to store in the array (max 15): ");
	fflush(stdout);
	scanf("%d", &arrayLength);
	printf("\nInput %d number of elements in the array : ", arrayLength);

	for(int idx = 0; idx < arrayLength; ++idx)
	{
		printf("\nelement - %d : ", idx + 1);
		fflush(stdout);
		scanf("%d", &array[idx]);
	}

	arrayPtr += arrayLength;
	idx = arrayLength;
	printf("\nThe elements of array in reverse order are :");

	while(--arrayPtr != array)
	{
		printf("\nelement - %d : %d", idx--, *arrayPtr);
	}
	printf("\nelement - %d : %d", idx--, *arrayPtr);

	return EXIT_SUCCESS;
}
