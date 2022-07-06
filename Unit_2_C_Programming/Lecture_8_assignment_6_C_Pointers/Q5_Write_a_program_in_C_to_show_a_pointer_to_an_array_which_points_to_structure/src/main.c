#include <stdio.h>
#include <stdlib.h>

#define EMPLOYER_NAME_MAX_LENGTH (128)

struct employer
{
	int id;
	char name[EMPLOYER_NAME_MAX_LENGTH];
};

int main()
{
	struct employer emp = {1002, "Alex"};
	struct employer *employerPtr = &emp;
	printf("Employer Name: %s\n", employerPtr->name);
	printf("Employer ID: %d", employerPtr->id);

	return EXIT_SUCCESS;
}
