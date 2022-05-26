#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int num, total = 0;

	printf("Enter an integer: ");
	fflush(stdout);
	scanf("%d", &num);

	while(num != 0)
	{
		total += num--;
	}

	printf("Sum = %d", total);

	return EXIT_SUCCESS;
}
