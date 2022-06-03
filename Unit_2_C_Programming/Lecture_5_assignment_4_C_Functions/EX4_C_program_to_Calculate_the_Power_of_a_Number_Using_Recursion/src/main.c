#include <stdio.h>
#include <stdlib.h>

int power(int num, int exp);

int main()
{
	int num, exp, result;

	printf("Enter base number: ");
	fflush(stdout);
	scanf("%d", &num);

	printf("Enter power number(positive integer): ");
	fflush(stdout);
	scanf("%d", &exp);

	result = power(num, exp);

	printf("%d^%d = %d", num, exp, result);

	return EXIT_SUCCESS;
}

int power(int num, int exp)
{
	if(exp == 0)
	{
		return 1;
	}

	return num *power(num, exp - 1);
}
