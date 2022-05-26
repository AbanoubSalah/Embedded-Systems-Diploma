#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char c;

	printf("Enter an alphabet: ");
	fflush(stdout);
	scanf("%c", &c);

	if((c == 'A') || (c == 'a') || (c=='E') || (c == 'e') || (c == 'I') || (c == 'i') || (c=='O') || (c == 'o') || (c == 'U') || (c == 'u'))
	{
		printf("%c is a vowel.", c);
	}
	else
	{
		printf("%c is a consonant.", c);
	}

	return EXIT_SUCCESS;
}
