#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	float num;

	printf("Enter a number: ");
	fflush(stdout);
	scanf("%f", &num);

	if(num < 0)
	{
		printf("%.2f is negative.", num);
	}
	else
	{
		if (num == 0)
		{
			printf("You entered zero.");
		}
		else
		{
			printf("%.2f is positive.", num);
		}
	}

	return EXIT_SUCCESS;
}
