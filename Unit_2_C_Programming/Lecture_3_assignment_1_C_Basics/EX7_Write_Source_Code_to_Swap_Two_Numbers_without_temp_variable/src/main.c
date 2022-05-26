#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	float a, b;
	  printf("Enter value of a: ");
	  scanf("%f", &a);
	  printf("Enter value of b: ");
	  scanf("%f", &b);
	  b += a;
	  a = b - a;
	  b -= a;
	  printf("\nAfter swapping, value of a = %.2f\n", a);
	  printf("After swapping, value of b = %.2f", b);
	
	return EXIT_SUCCESS;
}
