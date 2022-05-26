#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int number;
	printf("Enter a integer: ");
	fflush(stdout);
	scanf("%d", &number);
	printf("You entered: %d", number);
	
	return EXIT_SUCCESS;
}
