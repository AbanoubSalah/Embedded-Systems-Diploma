/******************************************************************************
 * @file fifo.h
 * @brief This file is the interface to a simple circular FIFO data structure
 *
 * @author Abanoub Salah
 * @date July 29, 2022
 * ****************************************************************************/

#ifndef FIFO_H_
#define FIFO_H_

#include "platform_types.h"
#include "student_database.h"

/* Configuring FIFO elements type and length */
#define ELEMENTS_TYPE 			studentInfo

/* Dequeue typedef */
typedef struct{
	uint32 length;
	ELEMENTS_TYPE *base;
	ELEMENTS_TYPE *tail;
	ELEMENTS_TYPE *head;
	uint32 count;
} FIFO_Buffer_t;

/* Dequeue status enumeration typedef */
typedef enum{
	FIFO_no_error,
	FIFO_fuLL,
	FIFO_not_full,
	FIFO_empty,
	FIFO_not_empty,
	FIFO_null
}FIFO_Buffer_Status;

/******************************************************************************
 * @brief Initiate the FIFO buffer
 *
 * This function initiates the FIFO structure buffer
 *
 * @param lBuff		Pointer to FIFO buffer
 * @param items		The elements array
 * @param length	FIFO length
 *
 * @return Operation result as buffer status
 ******************************************************************************/
FIFO_Buffer_Status FIFO_Init(FIFO_Buffer_t *lBuff , ELEMENTS_TYPE items[] , uint32 length);

/******************************************************************************
 * @brief Enqueue an item to the buffer
 *
 * This function checks if the buffer is valid and not full
 * Then enqueue the item at head and increases the count then checks
 * If head reached the end If it did it gets assigned the base address
 * Else increase base by one
 *
 * @param fBuff		Pointer to FIFO buffer
 * @param item		Pointer to an element to be enqueued
 *
 * @return Operation result as buffer status
 ******************************************************************************/
FIFO_Buffer_Status FIFO_Enqueue(FIFO_Buffer_t *fBuff, ELEMENTS_TYPE *item);

/******************************************************************************
 * @brief Dequeue an item from the buffer
 *
 * This function checks if the buffer is valid and not empty
 * Then dequeue the item at tail then decreases the count then checks
 * If tail reached the end if it did it gets assigned the base address
 * Else increase tail by one
 *
 * @param fBuff		Pointer to FIFO buffer
 * @param item		an Element to be enqueued
 *
 * @return Operation result as buffer status
 ******************************************************************************/
FIFO_Buffer_Status FIFO_Dequeue(FIFO_Buffer_t *fBuff, ELEMENTS_TYPE *item);

#endif /* FIFO_H_ */

/******************************************************************************
 *  END OF FILE: fifo.h
 ******************************************************************************/
