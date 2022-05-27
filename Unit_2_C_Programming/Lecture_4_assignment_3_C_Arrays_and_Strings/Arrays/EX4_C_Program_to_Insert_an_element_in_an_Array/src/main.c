#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int arr[100];
	int n = 0;
	int insertNum;
	int isertionIdx;

	printf("\nEnter no of elements : ");
	fflush(stdout);
	scanf("%d", &n);
	printf("\n");
	fflush(stdout);

	for(int idx = 0; idx < n; ++idx)
	{
		scanf("%d", &arr[idx]);
	}

	printf("\nEnter the element to be inserted : ");
	fflush(stdout);
	scanf("%d", &insertNum);

	printf("\nEnter the location : ");
	fflush(stdout);
	scanf("%d", &isertionIdx);

	for(int idx = n; idx >= isertionIdx; --idx)
	{
		arr[idx] = arr[idx - 1];
	}

	arr[isertionIdx - 1] = insertNum;

	printf("\n");
	++n;
	for(int idx = 0; idx < n; ++idx)
	{
		printf("%d ", arr[idx]);
	}

	return EXIT_SUCCESS;
}
