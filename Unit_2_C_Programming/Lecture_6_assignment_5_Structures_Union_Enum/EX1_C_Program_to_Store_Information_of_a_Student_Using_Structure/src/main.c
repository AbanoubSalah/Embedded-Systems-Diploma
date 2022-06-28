#include <stdio.h>
#include <stdlib.h>

#define NAME_MAX_LENGTH (50)

struct student
{
	float marks;
	int roll;
	char name[NAME_MAX_LENGTH];
};

int main()
{
	struct student stud1;

	printf("Enter information of student: \n\n");

	printf("Enter name: ");
	fflush(stdout);
	fgets(stud1.name, NAME_MAX_LENGTH, stdin);

	printf("Enter roll number: ");
	fflush(stdout);
	scanf("%d", &stud1.roll);

	printf("Enter marks: ");
	fflush(stdout);
	scanf("%f", &stud1.marks);

	printf("\nDisplaying Information\n");

	printf("name: %s\n", stud1.name);
	printf("Roll: %d\n", stud1.roll);
	printf("Marks:%.2f\n", stud1.marks);

	return EXIT_SUCCESS;
}
