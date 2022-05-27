#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char string[101];
	char character;
	int frequency = 0;

	printf("\nEnter a string: ");
	fflush(stdout);
	gets(string);

	printf("\nEnter a character to find frequency: ");
	fflush(stdout);
	scanf("%c", &character);

	for(int idx = 0; string[idx] != '\0'; ++idx )
	{
		if(string[idx] == character)
		{
			++frequency;
		}
	}

	printf("\nFrequency of %c = %d", character, frequency);

	return EXIT_SUCCESS;
}
