#include <stdio.h>
#include <stdlib.h>

#define STRING_MAX_LENGTH (100)

int main()
{
	char string[STRING_MAX_LENGTH];
	char *stringPtr;

	printf("Input a string: ");
	fflush(stdout);
	fgets(string, STRING_MAX_LENGTH, stdin);

	stringPtr = string;
	while(*stringPtr++ != '\0');

	stringPtr -= 2;

	printf("Reverse of the string is: ");

	while(stringPtr-- != string)
	{
		printf("%c", *stringPtr);
	}

	printf("%c", *stringPtr);

	return EXIT_SUCCESS;
}
