#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	float a[2][2], b[2][2];
	printf("Enter the elements of 1st matrix\n");

	for(int row = 0; row < 2; ++row )
	{
		for(int col = 0; col < 2; ++col )
		{
			printf("Enter a%d%d: ", row + 1, col + 1);
			fflush(stdout);
			scanf("%f", &a[row][col]);
		}
	}

	printf("Enter the elements of 2nd matrix\n");
	for(int row = 0; row < 2; ++row )
	{
		for(int col = 0; col < 2; ++col )
		{
			printf("Enter b%d%d: ", row + 1, col + 1);
			fflush(stdout);
			scanf("%f", &b[row][col]);
		}
	}

	printf("Sum Of Matrix:\n");
	for(int row = 0; row < 2; ++row )
		{
			for(int col = 0; col < 2; ++col )
			{
				printf("%.1f\t", a[row][col] + b[row][col]);
			}
			printf("\n");
		}

	return EXIT_SUCCESS;
}
