#include <stdio.h>
#include <stdlib.h>

#define NAME_MAX_LENGTH (50)
#define ROLL_MAX_LENGTH (10)

struct student
{
	int marks;
	int roll;
	char name[NAME_MAX_LENGTH];
};

int main()
{
	struct student stud[ROLL_MAX_LENGTH];

	printf("Enter information of students: \n");

	for(int i = 0; i < ROLL_MAX_LENGTH; ++i)
	{
		stud[i].roll = i + 1;

		printf("\nFor roll number %d\n", stud[i].roll);
		printf("Enter name: ");
		fflush(stdout);
		fgets(stud[i].name, NAME_MAX_LENGTH, stdin);

		printf("Enter marks: ");
		fflush(stdout);
		scanf("%d", &stud[i].marks);
		getchar();
	}

	printf("\nDisplaying information of students: \n");

	for(int i = 0; i < ROLL_MAX_LENGTH; ++i)
	{
		printf("\nInformation for roll number %d: \n", stud[i].roll);
		printf("name: %s", stud[i].name);
		printf("Marks: %d\n", stud[i].marks);
	}

	return EXIT_SUCCESS;
}
