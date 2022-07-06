#include <stdio.h>
#include <stdlib.h>

int main()
{
	const char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const char *curChar = alpha;

	while(*curChar != '\0')
	{
		printf("%c ", *curChar++);
	}

	return EXIT_SUCCESS;
}
