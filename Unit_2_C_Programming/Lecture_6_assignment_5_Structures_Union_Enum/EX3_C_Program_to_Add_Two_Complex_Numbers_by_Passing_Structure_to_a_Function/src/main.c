#include <stdio.h>
#include <stdlib.h>

struct complex
{
	float real;
	float imaginary;
};

struct complex addComplex(struct complex cmp1, struct complex cmp2)
{
	struct complex result;

	result.real = cmp1.real + cmp2.real;
	result.imaginary = cmp1.imaginary + cmp2.imaginary;

	return result;
}

int main()
{
	struct complex cmp1, cmp2, cmp3;

	printf("For lst complex number\n");
	printf("Enter real and imaginary respectively: ");
	fflush(stdout);
	scanf("%f %f", &cmp1.real, &cmp1.imaginary);

	printf("\nFor 2nd complex number\n");
	printf("Enter real and imaginary respectively: ");
	fflush(stdout);
	scanf("%f %f", &cmp2.real, &cmp2.imaginary);

	cmp3 = addComplex(cmp1, cmp2);

	printf("Sum = %.1f%+.1fi", cmp3.real, cmp3.imaginary);

	return EXIT_SUCCESS;
}
