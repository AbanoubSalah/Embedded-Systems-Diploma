#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	float a, b, temp;
	  printf("Enter value of a: ");
	  scanf("%f", &a);
	  printf("Enter value of b: ");
	  scanf("%f", &b);
	  temp = a;
	  a = b;
	  b = temp;
	  printf("\nAfter swapping, value of a = %.2f\n", a);
	  printf("After swapping, value of b = %.2f", b);
	
	return EXIT_SUCCESS;
}
