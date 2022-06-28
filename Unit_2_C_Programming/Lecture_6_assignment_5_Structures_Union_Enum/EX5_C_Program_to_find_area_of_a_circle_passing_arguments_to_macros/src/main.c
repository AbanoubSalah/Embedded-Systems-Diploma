#include <stdio.h>
#include <stdlib.h>

#define PI (3.14159265f)
#define CIRCLE_AREA(x) (PI*x*x)

int main()
{
	float radius;

	printf("Enter the radius: ");
	fflush(stdout);
	scanf("%f", &radius);

	printf("Area = %.2f", CIRCLE_AREA(radius));

	return EXIT_SUCCESS;
}
