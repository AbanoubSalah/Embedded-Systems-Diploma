/**
 * @file StudentDatabase.h
 * @brief This file is the interface to a student database using linked list
 *
 * @author Abanoub Salah
 * @date July 30, 2022
 *
 */

#ifndef FEATURES_H_
#define FEATURES_H_

#include "platform_types.h"

#define STUDENT_NAME_LENGTH		(50)

/* my printf macro */
#define MY_PRINTF(...)    	{printf(__VA_ARGS__); \
                       	   	   fflush(stdout); \
                       	   	   fflush(stdin);}

/* my fgets macro */
#define MY_FGETS(...)    	{fgets(__VA_ARGS__); \
                       	   	   fflush(stdin);}

/* Student database typedef */
typedef struct
{
	uint32 ID;
	char_t name[STUDENT_NAME_LENGTH];
	float height;
} Student_Data;

/* linked list node typedef */
typedef struct Student {
	Student_Data data;
	struct Student *next;
} Student_Database_t;

/* Student database status enumeration */
typedef enum {
	Student_Database_error,
	Student_Database_no_error,
	Student_Database_empty,
	Student_Database_done
} Student_Database_Status;

/**
 * @brief Add a student to the database
 *
 * Add a student to the end if list is not empty otherwise put it at head.
 *
 * @param head		Pointer to a pointer of student database
 * @param length	Student database length
 *
 * @return Operation result as student database status
 */
Student_Database_Status Student_Database_Add(Student_Database_t **head,
		uint32 *length);

/**
 * @brief Delete a student from the database by ID
 *
 * Deletes a student from the database by ID iterating over the linked list
 * if found it gets deleted.
 *
 * @param head		Pointer to a pointer of student database
 * @param length	Student database length
 *
 * @return Operation result as student database status
 */
Student_Database_Status Student_Database_Delete(Student_Database_t **head,
		uint32 *length);

/**
 * @brief Print out the entire student database
 *
 * Iterates over the entire linked list and prints out students one by one.
 *
 * @param head		Pointer to a pointer of student database
 * @param length	Student database length
 *
 * @return Operation result as student database status
 */
Student_Database_Status Student_Database_View(Student_Database_t **head);

/**
 * @brief Delete the entire student database
 *
 * Deletes the entire student database iterating over the linked list
 * deleting records one by one.
 *
 * @param head		Pointer to a pointer of student database
 * @param length	Student database length
 *
 * @return Operation result as student database status
 */
Student_Database_Status Student_Database_DeleteAll(Student_Database_t **head,
		uint32 *length);

/**
 * @brief Get the Nth student from start
 *
 * Get student by index from start by starting from head and
 * advancing head N times.
 *
 * @param head		Pointer to a pointer of student database
 * @param length	Student database length
 *
 * @return Operation result as student database status
 */
Student_Database_Status Student_Database_GetNthNodeFromStart(
		Student_Database_t **head, uint32 *length);

/**
 * @brief Get the Nth student from end
 *
 * Get student by index from end by two pointer slow points to head and
 * fast N times away from slow then advance both until fast reaches the end
 * of the linked list then return slow which points to the Nth student
 * from the end.
 *
 * @param head		Pointer to a pointer of student database
 * @param length	Student database length
 *
 * @return Operation result as student database status
 */
Student_Database_Status Student_Database_GetNthNodeFromEnd(
		Student_Database_t **head, uint32 *length);

/**
 * @brief Get length of the student database linked list
 *
 * Get length of the student database linked list by iterating over
 * the linked list and counting the nodes.
 *
 * @param head		Pointer to a pointer of student database
 *
 * @return Operation result as student database status
 */
Student_Database_Status Student_Database_GetLength(Student_Database_t **head);

/**
 * @brief Get the middle element of the student database
 *
 * get the middle element using two pointers slow moves by one step over
 * the linked list the second is fast moves with two steps until it reaches
 * a null node then the slow will contain the middle element with the first
 * node of the two middle nodes in the even case and the middle
 * element in the odd case.
 *
 * @param head		Pointer to a pointer of student database
 *
 * @return Operation result as student database status
 */
Student_Database_Status Student_Database_GetMiddle(Student_Database_t **head);

/**
 * @brief Detect loops within the student database linked list
 *
 * Detecting the loop by using two pointers slow moves one step at
 * a time in the linked list and fast moves two steps at a time by checking
 * if they both meet at some point then there is a loop if fast reaches a null
 * node then there is no loop.
 *
 * @param head		Pointer to a pointer of student database
 *
 * @return Operation result as student database status
 */
Student_Database_Status Student_Database_DetectLoop(Student_Database_t **head);

/**
 * @brief Reverse student database linked list
 *
 * reverse the list by walking over nodes pointing to the previous node
 * until reaching a null node.
 *
 * @param head		Pointer to a pointer of student database
 *
 * @return Operation result as student database status
 */
Student_Database_Status Student_Database_Reverse(Student_Database_t **head);

#endif /* FEATURES_H_ */
