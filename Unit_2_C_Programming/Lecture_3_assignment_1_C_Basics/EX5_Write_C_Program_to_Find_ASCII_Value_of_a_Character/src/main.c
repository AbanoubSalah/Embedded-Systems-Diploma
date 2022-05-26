#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char asciiChar;
	printf("Enter a character: ");
	scanf("%c", &asciiChar);
	printf("ASCII value of %c = %d", asciiChar, asciiChar);
	
	return EXIT_SUCCESS;
}
