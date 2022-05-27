#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int arr[100];
	int n = 0;
	int findNum;
	int foundIdx = -1;

	printf("\nEnter no of elements : ");
	fflush(stdout);
	scanf("%d", &n);
	printf("\n");
	fflush(stdout);

	for(int idx = 0; idx < n; ++idx)
	{
		scanf("%d", &arr[idx]);
	}

	printf("\nEnter the elements to be searched : ");
	fflush(stdout);
	scanf("%d", &findNum);

	for(int idx = 0; idx < n; ++idx)
	{
		if(arr[idx] == findNum)
		{
			foundIdx = idx;
		}
	}

	if(foundIdx != -1)
	{
		printf("Number found at the location = %d", foundIdx + 1);
	}
	else
	{
		printf("Number was not found");
	}

	return EXIT_SUCCESS;
}
