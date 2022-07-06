#include <stdio.h>
#include <stdlib.h>

int main()
{

	int m = 29;
	int *ab;

	printf("\nAddress of m : %#x", &m);
	printf("\nValue of m : %d", m);

	ab = &m;

	printf("\nNow ab is assigned with the address of m.");
	printf("\nAddress of pointer ab : %#x", ab);
	printf("\nContent of pointer ab : %d", *ab);

	m = 34;

	printf("\nThe value of m assigned to 34 now.");
	printf("\nAddress of pointer ab : %#x", ab);
	printf("\nContent of pointer ab : %d", *ab);

	*ab = 7;

	printf("\nThe pointer variable ab is assigned with the value 7 now.");
	printf("\nAddress of m : %#x", &m);
	printf("\nValue of m : %d", m);


	return EXIT_SUCCESS;
}
