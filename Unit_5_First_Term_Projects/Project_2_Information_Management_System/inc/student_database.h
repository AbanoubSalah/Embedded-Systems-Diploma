/******************************************************************************
 * @file student_database.h
 * @brief This file is the interface to a student database using FIFO
 *
 * @author Abanoub Salah
 * @date September 17, 2022
 * ****************************************************************************/

#ifndef STUDENT_DATABASE_H_
#define STUDENT_DATABASE_H_

#include "platform_types.h"

#define MAX_STUDENT_NAME_LENGTH			(50)
#define MAX_STUDENTS_NUMBER				(55)
#define MAX_MENU_OPTIONS_CHARACTERS		(5)
#define MAX_SUBJECTS_OPTIONS			(5)
#define MAX_INPUT_NUMBER				(11)

/* my printf macro */
#define MY_PRINTF(...)    				{printf(__VA_ARGS__); \
                       	   	   	   	   	   	   fflush(stdout);\
                       	   	   	   	   	   	   fflush(stdin);}

/* my fgets macro */
#define MY_FGETS(...)    				{fgets(__VA_ARGS__); \
                       	   	   	   	   	   	   fflush(stdin);}

/* Student database typedef */
typedef struct
{
	char_t firstName[MAX_STUDENT_NAME_LENGTH];
	char_t lastName[MAX_STUDENT_NAME_LENGTH];
	uint32 studentRollNumber;
	float GPA;
	uint32 coursesID[MAX_SUBJECTS_OPTIONS];
} studentInfo;

/* Student database status enumeration */
typedef enum
{
	Student_Database_error,
	Student_Database_no_error,
	Student_Database_empty,
	Student_Database_done
} studentDatabase_Status;

/******************************************************************************
 * @brief Initialize the student database
 *
 * Initialize the student database FIFO
 *
 * @param None
 *
 * @returns None
 ******************************************************************************/
void studentDatabaseInit(void);

/******************************************************************************
 * @brief Add a student to the database manually
 *
 * Add a student to the database manually from standard input
 *
 * @param None
 *
 * @returns Operation result as student database status
 ******************************************************************************/
studentDatabase_Status AddStudentManually(void);

/******************************************************************************
 * @brief Add a student to the database from a file
 *
 * Add a student to the database from a text file
 *
 * @param None
 *
 * @returns Operation result as student database status
 ******************************************************************************/
studentDatabase_Status AddStudentFromFile(void);

/******************************************************************************
 * @brief Find a student by roll number
 *
 * Find a student by roll number
 *
 * @param None
 *
 * @returns Operation result as student database status
 ******************************************************************************/
studentDatabase_Status FindStudentByRollNumber(void);

/******************************************************************************
 * @brief Find a student by first name
 *
 * Find a student by first name
 *
 * @param None
 *
 * @returns Operation result as student database status
 ******************************************************************************/
studentDatabase_Status FindStudentByFirstName(void);

/******************************************************************************
 * @brief Find students that is enrolled to a course
 *
 * Find students that is enrolled to a course by course ID
 *
 * @param None
 *
 * @returns Operation result as student database status
 ******************************************************************************/
studentDatabase_Status FindStudentsByCourseID(void);

/******************************************************************************
 * @brief Find the total number students
 *
 * Find the total number students
 *
 * @param None
 *
 * @returns Operation result as student database status
 ******************************************************************************/
studentDatabase_Status FindStudentTotalNumber(void);

/******************************************************************************
 * @brief Delete a student by roll number
 *
 * Delete a student by roll number
 *
 * @param None
 *
 * @returns Operation result as student database status
 ******************************************************************************/
studentDatabase_Status DeleteStudentbyRollNumber(void);

/******************************************************************************
 * @brief Update a student by roll number
 *
 * Update a student by roll number
 *
 * @param None
 *
 * @returns Operation result as student database status
 ******************************************************************************/
studentDatabase_Status UpdateStudentbyRollNumber(void);

/******************************************************************************
 * @brief Show all students information
 *
 * Show all students information by printing to the standard output
 *
 * @param None
 *
 * @returns Operation result as student database status
 ******************************************************************************/
studentDatabase_Status ShowStudentsInformation(void);

#endif /* STUDENT_DATABASE_H_ */

/******************************************************************************
 *  END OF FILE: student_database.h
 ******************************************************************************/
