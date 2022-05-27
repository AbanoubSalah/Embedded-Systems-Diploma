#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char string[100];
	int strLength = 0;

	printf("\nEnter the string: ");
	fflush(stdout);
	gets(string);


	strLength = strlen(string);

	for(int idx = 0; idx < strLength / 2; ++idx)
	{
		char tmp = string[idx];
		string[idx] = string[strLength - idx - 1];
		string[strLength - idx - 1] = tmp;

	}

	printf("Reverse string is: %s", string);

	return EXIT_SUCCESS;
}
