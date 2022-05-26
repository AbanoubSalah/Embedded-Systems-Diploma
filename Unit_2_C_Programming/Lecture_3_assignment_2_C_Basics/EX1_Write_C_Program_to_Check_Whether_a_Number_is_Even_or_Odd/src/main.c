#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int num;

	printf("Enter an integer you want to check: ");
	scanf("%d", &num);

	if((num & 1) == 0)
	{
		printf("%d is even.", num);
	}
	else
	{
		printf("%d is odd.", num);
	}

	return EXIT_SUCCESS;
}
