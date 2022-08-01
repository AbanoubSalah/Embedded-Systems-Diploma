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
#include <StudentDatabase.h>
#include "platform_types.h"

sint32 main()
{
	char_t option[5];
	Student_Database_t *Student_Database_head = NULL;
	uint32 Student_Database_length = 0;

	while(TRUE)
	{
		//print the main menu
		printf("\nPick an Option from the list:   \n");
		printf("_________________________________ \n");
		printf("1 : Add student                   \n");
		printf("2 : Delete student                \n");
		printf("3 : view students                 \n");
		printf("4 : Delete all                    \n");
		printf("5 : Get Nth of node from start    \n");
		printf("6 : Get Nth of node from end      \n");
		printf("7 : Find the length               \n");
		printf("8 : Find the middle               \n");
		printf("9 : Detect loop                   \n");
		printf("10: Reverse                       \n");
		printf("11: Exit                          \n");
		printf("_________________________________ \n");

		MY_PRINTF("Enter an option: ");
		MY_FGETS(option, 5, stdin);

		//Options switching
		switch(strtol(option, NULL, 10))
		{
			case 1:
				Student_Database_Add(&Student_Database_head,
						&Student_Database_length);
				break;
			case 2:
				Student_Database_Delete(&Student_Database_head,
						&Student_Database_length);
				break;
			case 3:
				Student_Database_View(&Student_Database_head);
				break;
			case 4:
				Student_Database_DeleteAll(&Student_Database_head,
						&Student_Database_length);
				break;
			case 5:
				Student_Database_GetNthNodeFromStart(&Student_Database_head,
						&Student_Database_length);
				break;
			case 6:
				Student_Database_GetNthNodeFromEnd(&Student_Database_head,
						&Student_Database_length);
				break;
			case 7:
				Student_Database_GetLength(&Student_Database_head);
				break;
			case 8:
				Student_Database_GetMiddle(&Student_Database_head);
				break;
			case 9:
				/* To test Student_Database_DetectLoop function un-comment
				 * the following code block but note to add at least three
				 * student records so the program would not crash. */

				/* Student_Database_head->next->next = Student_Database_head; */
				Student_Database_DetectLoop(&Student_Database_head);
				break;
			case 10:
				Student_Database_Reverse(&Student_Database_head);
				break;
			case 11:
				exit(0);
				break;
			default:
				printf("Wrong Option!!!\n");
				break;
		}
	}

	return EXIT_SUCCESS;
}
