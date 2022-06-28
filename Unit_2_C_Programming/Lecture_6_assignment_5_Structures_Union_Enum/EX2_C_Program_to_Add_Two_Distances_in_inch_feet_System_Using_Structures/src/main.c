#include <stdio.h>
#include <stdlib.h>

struct distance
{
	int feet;
	float inch;
};

int main()
{
	struct distance dist1, dist2, dist3;

	printf("Enter information for lst distance\n");
	printf("Enter feet: ");
	fflush(stdout);
	scanf("%d", &dist1.feet);
	printf("Enter feet: ");
	fflush(stdout);
	scanf("%f", &dist1.inch);

	printf("\nEnter information for 2nd distance\n");
	printf("Enter feet: ");
	fflush(stdout);
	scanf("%d", &dist2.feet);
	printf("Enter feet: ");
	fflush(stdout);
	scanf("%f", &dist2.inch);

	dist3.feet = dist1.feet + dist2.feet;
	dist3.inch = dist1.inch + dist2.inch;
	while(dist3.inch > 12)
	{
		++dist3.feet;
		dist3.inch -= 12;
	}

	printf("Sum of distances = %d'%.2f\"", dist3.feet, dist3.inch);

	return EXIT_SUCCESS;
}
