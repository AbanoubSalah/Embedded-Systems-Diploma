/**
 * @file main.c
 * @brief This file is the driver for a student database using linked list
 *
 * @author Abanoub Salah
 * @date July 31, 2022
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "platform_types.h"
#include "student_database.h"
#include "fifo.h"

int main()
{
	char_t option[MAX_MENU_OPTIONS_CHARACTERS];

	studentDatabaseInit();

	while(TRUE)
	{
		/* print the main menu */
		MY_PRINTF("---------------------------------------------   \n");
		MY_PRINTF("Choose The Task that you want to perform:       \n");
		MY_PRINTF("---------------------------------------------   \n");
		MY_PRINTF("l.  Add the Student Details Manually			   \n");
		MY_PRINTF("2.  Add the Student Details From Text File	   \n");
		MY_PRINTF("3.  Find the Student Details by Roll Number	   \n");
		MY_PRINTF("4.  Find the Student Details by First Name	   \n");
		MY_PRINTF("S.  Find the Student Details by Course Id	   \n");
		MY_PRINTF("6.  Find the Total number of Students		   \n");
		MY_PRINTF("7.  Delete the Students Details by Roll Number  \n");
		MY_PRINTF("8.  Update the Students Details by Roll Number  \n");
		MY_PRINTF("9.  Show all information						   \n");
		MY_PRINTF("l0. To Exit									   \n");
		MY_PRINTF("---------------------------------------------   \n");

		MY_PRINTF("\nEnter your choice to perform the task: ");
		MY_FGETS(option, MAX_MENU_OPTIONS_CHARACTERS, stdin);

		//Options switching
		switch(strtol(option, NULL, 10))
		{
			case 1:
				AddStudentManually();
				break;
			case 2:
				AddStudentFromFile();
				break;
			case 3:
				FindStudentByRollNumber();
				break;
			case 4:
				FindStudentByFirstName();
				break;
			case 5:
				FindStudentsByCourseID();
				break;
			case 6:
				FindStudentTotalNumber();
				break;
			case 7:
				DeleteStudentbyRollNumber();
				break;
			case 8:
				UpdateStudentbyRollNumber();
				break;
			case 9:
				/* Student_Database_head->next->next = Student_Database_head; */
				ShowStudentsInformation();
				break;
			case 10:
				MY_PRINTF("Exiting...\n");
				exit(EXIT_SUCCESS);
				break;
			default:
				MY_PRINTF("Wrong Option!!!\n");
				break;
		}
	}

	return EXIT_SUCCESS;
}
