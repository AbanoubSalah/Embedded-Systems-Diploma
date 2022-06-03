#include <stdio.h>
#include <stdlib.h>

int factorial(int num);

int main()
{
	int num, numFactorial;

	printf("Enter an positive integer: ");
	fflush(stdout);
	scanf("%d", &num);

	numFactorial = factorial(num);
	printf("Factorial of %d = %d", num, numFactorial);

	return EXIT_SUCCESS;
}

int factorial(int num)
{
	if(num == 1)
	{
		return 1;
	}

	return num * factorial(num - 1);
}
