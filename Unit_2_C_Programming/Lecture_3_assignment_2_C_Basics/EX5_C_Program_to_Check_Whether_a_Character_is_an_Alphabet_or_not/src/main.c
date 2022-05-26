#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char c;

	printf("Enter a character: ");
	fflush(stdout);
	scanf("%c", &c);

	if(((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')))
	{
		printf("%c is an alphabet.", c);
	}
	else
	{
		printf("%c is not an alphabet.", c);
	}

	return EXIT_SUCCESS;
}
