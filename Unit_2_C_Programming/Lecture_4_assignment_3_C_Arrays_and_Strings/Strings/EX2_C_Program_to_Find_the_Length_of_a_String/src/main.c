#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char string[100];
	int strLength = 0;

	printf("\nEnter a string: ");
	fflush(stdout);
	gets(string);


	while(string[strLength++] != '\0');

	printf("\nLength of string: %d", --strLength);

	return EXIT_SUCCESS;
}
