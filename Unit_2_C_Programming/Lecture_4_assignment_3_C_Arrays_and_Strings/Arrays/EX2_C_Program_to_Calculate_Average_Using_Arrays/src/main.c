#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int n = 0;
	float numsArray[100];
	float average = 0;

	printf("Enter the numbers of data: ");
	fflush(stdout);
	scanf("%d", &n);

	for(int idx = 0; idx < n; ++idx)
	{
		printf("%2d. Enter number: ", idx + 1);
		fflush(stdout);
		scanf("%f", &numsArray[idx]);
		average += numsArray[idx];
	}

	average /= n;
	printf("Average = %.2f", average);

	return EXIT_SUCCESS;
}
