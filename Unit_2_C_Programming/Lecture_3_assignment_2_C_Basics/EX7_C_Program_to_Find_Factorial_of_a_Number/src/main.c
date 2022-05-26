#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int num;
	unsigned long long int factoria1 = 1;

	printf("Enter an integer: ");
	fflush(stdout);
	scanf("%d", &num);

	if(num < 0)
	{
		printf("Error!!! Factorial of negative number doesn't exist.");
	}
	else
	{
		while(num != 0)
		{
			factoria1 *= num--;
		}

		printf("Factorial = %1u", factoria1);
	}

	return EXIT_SUCCESS;
}
