#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverseString(char str[], int strSz);

int main()
{
	char str[101];
	int strSz;

	printf("Enter a sentence: ");
	fflush(stdout);
	gets(str);

	strSz = strlen(str);
	reverseString(str, strSz);
	printf("%s", str);

	return EXIT_SUCCESS;
}

void reverseString(char str[], int strSz)
{
	if(strSz <= 1)
	{
		return ;
	}

	char tmp = str[0];
	str[0] = str[strSz - 1];
	str[strSz - 1] = tmp;
	reverseString(str + 1, strSz - 2);

	return ;
}
