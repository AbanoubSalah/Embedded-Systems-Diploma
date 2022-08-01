/**
 * @file lifo.h
 * @brief This file is the interface to a simple LIFO data structure
 *
 * @author Abanoub Salah
 * @date July 29, 2022
 *
 */

#ifndef INC_LIFO_H_
#define INC_LIFO_H_

#include "platform_types.h"

/* Configuring LIFO elements type(uint8, uint16, uint32, ...) & length */
#define ELEMENTS_TYPE 			uint8
#define LIFO_BUFFER_LENGTH 		5

/* Stack typedef */
typedef struct{
	uint32 length;
	ELEMENTS_TYPE *base;
	ELEMENTS_TYPE *head;
	uint32 count;
} LIFO_Buffer_t;

/* Stack buffer status enumeration */
typedef enum{
	LIFO_no_error,
	LIFO_fuLL,
	LIFO_not_full,
	LIFO_empty,
	LIFO_not_empty,
	LIFO_null
}LIFO_Buffer_Status;

/**
 * @brief Initiate the LIFO buffer
 *
 * This function initiate the LIFO structure buffer
 *
 * @param lBuff		Pointer to LIFO buffer
 * @param items		The elements array
 * @param length	LIFO length
 *
 * @return Operation result as Buffer_status
 */
LIFO_Buffer_Status LIFO_INIT(LIFO_Buffer_t *lBuff , ELEMENTS_TYPE items[] , uint32 length);

/**
 * @brief Push an item to the buffer
 *
 * This function checks if the buffer is valid and not full
 * Then pushes an element to the buffer and increases the head
 * And also increases the elements count
 *
 * @param lBuff		Pointer to LIFO buffer
 * @param item		an Element to be pushed
 *
 * @return Operation result as buffer status
 */
LIFO_Buffer_Status LIFO_Push(LIFO_Buffer_t *lBuff, ELEMENTS_TYPE item);

/**
 * @brief Arbitrary function to quiz students on allocation
 *
 * This function checks if the buffer is valid and not empty
 * Then decreases the head and also decreases the elements count
 *
 * @param lBuff		Pointer to LIFO buffer
 * @param item		an Element to be popped
 *
 * @return Random integer value
 */
LIFO_Buffer_Status LIFO_Pop(LIFO_Buffer_t *lBuff, ELEMENTS_TYPE *item);

/**
 * @brief Prints buffer contents to stdout
 *
 * This function Prints the buffer contents to stdout
 *
 * @param lBuff	Pointer to LIFO buffer
 *
 * @return Operation result as buffer status
 */
LIFO_Buffer_Status LIFO_Print(LIFO_Buffer_t *lBuff);

#endif /* INC_LIFO_H_ */
