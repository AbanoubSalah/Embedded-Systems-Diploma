#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	float num1, num2;
	printf("Enter two numbers: ");
	scanf("%f %f",&num1, &num2);
	printf("Product: %f", num1 * num2);
	
	return EXIT_SUCCESS;
}
