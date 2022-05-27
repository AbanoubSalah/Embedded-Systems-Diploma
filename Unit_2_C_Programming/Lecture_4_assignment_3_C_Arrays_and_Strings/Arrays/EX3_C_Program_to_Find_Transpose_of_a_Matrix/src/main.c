#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int a[10][10], transpose[10][10];
	int rowSz = 0, colSz = 0;

	printf("Enter rows and column of matrix: ");
	fflush(stdout);
	scanf("%d %d", &rowSz, &colSz);

	printf("Enter elements of matrix:\n");
	for(int row = 0; row < rowSz; ++row )
	{
		for(int col = 0; col < colSz; ++col )
		{
			printf("Enter Elements a%d%d: ", row + 1, col + 1);
			fflush(stdout);
			scanf("%d", &a[row][col]);
		}
	}

	printf("\nEntered Matrix:\n");
	for(int row = 0; row < rowSz; ++row )
	{
		for(int col = 0; col < colSz; ++col )
		{
			printf("%d\t", a[row][col]);
		}
		printf("\n\n");
	}
	fflush(stdout);

	for(int row = 0; row < rowSz; ++row )
	{
		for(int col = 0; col < colSz; ++col )
		{
			transpose[col][row] = a[row][col];
		}
	}

	printf("\nTranspose of Matrix:\n");
	for(int row = 0; row < colSz; ++row )
	{
		for(int col = 0; col < rowSz; ++col )
		{
			printf("%d\t", transpose[row][col]);
		}
		printf("\n\n");
	}
	fflush(stdout);

	return EXIT_SUCCESS;
}
