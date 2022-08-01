/**
 * @file StudentDatabase.c
 * @brief This file is the implementation for a student database using
 *  linked list
 *
 * @author Abanoub Salah
 * @date July 30, 2022
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <StudentDatabase.h>
#include "platform_types.h"

/* Local function to fill in a student database node */
static void Student_Database_Fill(Student_Database_t *newStudent)
{
	char_t tmpC[50];

	MY_PRINTF("\nEnter student ID: ");
	MY_FGETS(tmpC, 11, stdin);
	newStudent->data.ID = strtol(tmpC, NULL, 11);

	MY_PRINTF("Enter student full name: ");
	MY_FGETS(newStudent->data.name, STUDENT_NAME_LENGTH, stdin);

	MY_PRINTF("Enter student height: ");
	MY_FGETS(tmpC, 11, stdin);
	newStudent->data.height = atoi(tmpC);

	newStudent->next = NULL;
}

/* Local function to find the student database length recursively */
static sint32 Student_Database_FindLength(Student_Database_t *head)
{
	if(head != NULL)
	{
		return 1 + Student_Database_FindLength(head->next);
	}
	else
	{
		return 0;
	}
}

Student_Database_Status Student_Database_Add(Student_Database_t **head,
		uint32 *length)
{
	/* allocate new record in the heap */
	Student_Database_t *pNewStudent = (Student_Database_t *)
			malloc(sizeof(Student_Database_t));

	/* check if memory allocation succeeded */
	if(pNewStudent == NULL)
	{
		MY_PRINTF("\nStudent_Database_Status: Couldn't allocate memory for"
				" a new student!!!");

		return Student_Database_error;
	}

	/* Check for an empty list */
	if(*head == NULL)
	{
		*head = pNewStudent;
	}
	else
	{
		/* Get the last student */
		Student_Database_t *pLastStudent = *head;
		while(pLastStudent->next)
		{
			pLastStudent = pLastStudent->next;
		}

		pLastStudent->next = pNewStudent;
    }

	/* fill student data */
	Student_Database_Fill(pNewStudent);

	/* increase length by one */
	(*length)++;

	return Student_Database_no_error;
}

Student_Database_Status Student_Database_Delete(Student_Database_t **head,
		uint32 *length)
{
	Student_Database_t *prvStudent = NULL, *curStudent = *head;
	char_t charStudentID[20];
	char_t confirmDelete[2];
	uint32 numStudentID;

	/* Get the desired user ID */
	MY_PRINTF("\nEnter student ID: ");
	MY_FGETS(charStudentID, 11, stdin);
	numStudentID = strtol(charStudentID, NULL, 11);

	while(TRUE)
	{
		MY_PRINTF("\nAre you sure that you want to delete student ID %u enter"
				" y for yes or n for no: ", numStudentID);
		MY_FGETS(confirmDelete, 4, stdin);

		if(confirmDelete[0] == 'y')
		{
			break;
		}
		else if(confirmDelete[0] == 'n')
		{
			return Student_Database_done;
		}
	}

	/* Get user by ID */
	while((curStudent != NULL) && (curStudent->data.ID != numStudentID))
	{
		prvStudent = curStudent;
		curStudent = curStudent->next;
	}

	/* Check for a valid user */
	if(curStudent == NULL)
	{
		MY_PRINTF("Could not find a student with the specified ID\n");

		return Student_Database_error;
	}

	/* Re-link in-between nodes */
	if(prvStudent == NULL)
	{
		*head = NULL;
	}
	else
	{
		prvStudent->next = curStudent->next;
	}

	/* free deleted user's memory */
	free(curStudent);
	(*length)--;
	MY_PRINTF("Student record with the ID %u was deleted successfully\n",
			numStudentID);
	MY_PRINTF("_________________________________\n");

	return Student_Database_done;
}

Student_Database_Status Student_Database_View(Student_Database_t **head)
{
	uint32 counter = 0;
	/* set direction pointer */
	Student_Database_t *pCurStudent = *head;

	/* list is empty */
	if(*head == NULL)
	{
		MY_PRINTF("list is empty\n");
		MY_PRINTF("_________________________________\n");

		return Student_Database_empty;
	}

	MY_PRINTF("\nStudents database dump:\n");
	while(pCurStudent != NULL)
	{
		/* while list is not empty print a record */
		MY_PRINTF("Record number %d\n", counter++);
		MY_PRINTF("\tID    : %d\n", pCurStudent->data.ID);
		MY_PRINTF("\tName  : %s", pCurStudent->data.name);
		MY_PRINTF("\tHeight: %f\n", pCurStudent->data.height);

		/* Go to next student */
		pCurStudent = pCurStudent->next;
	}

	MY_PRINTF("_________________________________\n");

	return Student_Database_done;

}

Student_Database_Status Student_Database_DeleteAll(
		Student_Database_t **head, uint32 *length)
{
	Student_Database_t *pCurStudent = NULL;

	/* list is already empty */
	if(*head == NULL)
	{
		MY_PRINTF("list is already empty!!!\n");
		MY_PRINTF("_________________________________\n");

		return Student_Database_empty;
	}

	while(*head != NULL)
	{
		/* while list is not empty free a record */
		pCurStudent = (*head)->next;
		free(*head);
		*head = pCurStudent;
	}

	/* Set length to zero */
	*length = 0;

	return Student_Database_done;
}

Student_Database_Status Student_Database_GetNthNodeFromStart(
		Student_Database_t **head, uint32 *length)
{
	uint32 StudentNum;
	char_t tmpC[11];
	Student_Database_t *pCurStudent = *head;

	/* Check for an empty list */
	if(*head == NULL)
	{
		MY_PRINTF("List is empty\n");
		MY_PRINTF("_________________________________\n");

		return Student_Database_empty;
	}

	MY_PRINTF("\nEnter student index(first): ");
	MY_FGETS(tmpC, 11, stdin);
	StudentNum = strtol(tmpC, NULL, 11);

	/* Check if N is bigger than total length */
	if(StudentNum >= *length)
	{
		MY_PRINTF("This index does not exist\n");
		MY_PRINTF("_________________________________\n");
		return Student_Database_error;
	}

	/* Walk the list until N is zero */
	while(StudentNum != 0)
	{
		pCurStudent = pCurStudent->next;
		--StudentNum;
	}

	MY_PRINTF("Record Student of index %d\n", (uint32)strtol(tmpC, NULL, 11));
	MY_PRINTF("\tID    : %d\n",pCurStudent->data.ID);
	MY_PRINTF("\tName  : %s",pCurStudent->data.name);
	MY_PRINTF("\tHeight: %f\n",pCurStudent->data.height);
	MY_PRINTF("_________________________________\n");

	return Student_Database_done;
}

Student_Database_Status Student_Database_GetNthNodeFromEnd(
		Student_Database_t **head, uint32 *length)
{
	Student_Database_t *pSlowStudent = *head, *pFastStudent = *head;
	uint32 StudentNum;
	char_t tmpC[11];

	/* Check for an empty list */
	if(*head == NULL)
	{
		MY_PRINTF("List is empty\n");
		MY_PRINTF("_________________________________\n");

		return Student_Database_empty;
	}

	MY_PRINTF("\nEnter student index(first): ");
	MY_FGETS(tmpC, 11, stdin);
	StudentNum = strtol(tmpC, NULL, 11);

	/* Check if N is bigger than total length */
	if(StudentNum >= *length)
	{
		MY_PRINTF("This index does not exist\n");
		MY_PRINTF("_________________________________\n");
		return Student_Database_error;
	}

	/* Walk the list until fast is N far from slow */
	while(StudentNum > 0)
	{
		pFastStudent = pFastStudent->next;
		StudentNum--;
	}

	/* Walk the list until fast reaches a null node */
	while(pFastStudent->next != NULL)
	{
		pSlowStudent = pSlowStudent->next;
		pFastStudent = pFastStudent->next;
	}

	MY_PRINTF("Record Student of index %d\n", (uint32)strtol(tmpC, NULL, 11));
	MY_PRINTF("\tID    : %d\n", pSlowStudent->data.ID);
	MY_PRINTF("\tName  : %s", pSlowStudent->data.name);
	MY_PRINTF("\tHeight: %f\n", pSlowStudent->data.height);
	MY_PRINTF("_________________________________\n");

	return Student_Database_done;
}

Student_Database_Status Student_Database_GetLength(Student_Database_t **head)
{
	uint32 length;
	char_t tmpC[11];

	MY_PRINTF("\nPick an option recursive(1)/iterative(2): ");
	fflush(stdin);
	MY_FGETS(tmpC, 11, stdin);

	switch(strtol(tmpC, NULL, 10))
	{
		/* recursive method */
		case 1:
			length = Student_Database_FindLength(*head);
			break;

		/* iterative method */
		case 2:
			Student_Database_t *pCurStudent = *head;
			length = 0;
			while(pCurStudent != NULL)
			{
				pCurStudent = pCurStudent->next;
				++length;
			}
			break;
		default:
			MY_PRINTF("Invalid option!!!\n");
			MY_PRINTF("_________________________________  \n");
			return Student_Database_error;
			break;
	}

	MY_PRINTF("length is %d\n", length);
	MY_PRINTF("_________________________________\n");

	return Student_Database_done;
}

Student_Database_Status Student_Database_GetMiddle(Student_Database_t **head)
{
	uint32 counter = 1;
	Student_Database_t *pSlowStudent = *head, *pFastStudent = *head;

	/* Check for an empty list */
	if(*head == NULL)
	{
		MY_PRINTF("List is empty\n");
		MY_PRINTF("_________________________________\n");

		return Student_Database_empty;
	}

	/* Slow moves one step and fast moves two steps until fast reaches the end
	 */
	while(pFastStudent != NULL)
	{
		if((pFastStudent->next != NULL) && (pFastStudent->next->next != NULL))
		{
			pFastStudent = pFastStudent->next->next;
		}
		else
		{
			break;
		}
		pSlowStudent = pSlowStudent->next;
		++counter;
	}

	MY_PRINTF("Record Student of index %d\n", counter);
	MY_PRINTF("\tID    : %d\n", pSlowStudent->data.ID);
	MY_PRINTF("\tName  : %s\n", pSlowStudent->data.name);
	MY_PRINTF("\tHeight: %f\n", pSlowStudent->data.height);
	MY_PRINTF("_________________________________\n");

	return Student_Database_done;
}

Student_Database_Status Student_Database_DetectLoop(Student_Database_t **head)
{
	Student_Database_t *pSlowStudent = *head, *pFastStudent = *head;

	/* Check for an empty list */
	if(*head == NULL)
	{
		MY_PRINTF("List is empty\n");
		MY_PRINTF("_________________________________\n");

		return Student_Database_empty;
	}

	/* Slow moves one step and fast moves two steps if fast reaches slow
	 *  then it is a loop otherwise fast reaches null node then
	 *   it is not a loop */
	while((pSlowStudent != NULL) && (pFastStudent != NULL) &&
			(pFastStudent->next != NULL))
	{
		pSlowStudent = pSlowStudent->next;
	    pFastStudent = pFastStudent->next->next;
	    if(pSlowStudent == pFastStudent)
	    {
			MY_PRINTF("\na Loop was found within the linked list!!!\n");
			MY_PRINTF("_________________________________\n");

			return Student_Database_done;
	    }
	}

	MY_PRINTF("\nThere is no loops within the linked list.\n");
	MY_PRINTF("_________________________________\n");

	return Student_Database_done;
}

Student_Database_Status Student_Database_Reverse(Student_Database_t **head)
{
	Student_Database_t * pPrvStudent = NULL, *pCurStudent = *head;
	Student_Database_t *pNxtStudent;

	/* Check for an empty list */
	if(*head == NULL)
	{
		MY_PRINTF("\nList is empty!!!\n");
		MY_PRINTF("_________________________________\n");

		return Student_Database_empty;
	}

	/* By moving from node to node and turn over next pointer to point to
	 *  the previous node */
	pNxtStudent = pCurStudent->next;
	while(pCurStudent != NULL)
	{
		pCurStudent->next = pPrvStudent;
		pPrvStudent = pCurStudent;
		pCurStudent = pNxtStudent;
		if(pNxtStudent != NULL)
		{
			pNxtStudent = pNxtStudent->next;
		}
	}

	*head = pPrvStudent;

	return Student_Database_done;
}
