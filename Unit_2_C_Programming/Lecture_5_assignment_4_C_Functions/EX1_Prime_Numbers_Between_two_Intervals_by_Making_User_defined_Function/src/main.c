#include <stdio.h>
#include <stdlib.h>

int isPrime(int num);

int main()
{
	int lowerLim, upperLim;

	printf("Enter two numbers(intervals): ");
	fflush(stdout);
	scanf("%d%d", &lowerLim, &upperLim);

	printf("Prime numbers between %d and %d are: ", lowerLim, upperLim);

	if(lowerLim < 3)
	{
		lowerLim = 3;
	}

	if((lowerLim & 1) == 0)
	{
		++lowerLim;
	}

	for(int num = lowerLim; num <= upperLim; num += 2)
	{
		int prime = isPrime(num);

		if( prime == 1 )
		{
			printf("%d ", num);
		}
	}

	return EXIT_SUCCESS;
}

int isPrime(int num)
{
	int isPrime = 1;

	if((num & 1) == 0)
	{
		return 0;
	}

	for(int i = 3; i < num; i += 2)
	{
		if((num % i) == 0)
		{
			isPrime = 0;
			break;
		}
	}

	return isPrime;
}
