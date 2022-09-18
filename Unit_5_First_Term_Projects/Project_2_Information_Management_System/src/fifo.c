/******************************************************************************
 * @file fifo.c
 * @brief This file is the implementation to a simple circular FIFO
 * 		  data structure.
 * @author Abanoub Salah
 * @date July 29, 2022
 * ****************************************************************************/


#include "fifo.h"
#include "platform_types.h"


FIFO_Buffer_Status FIFO_Init(FIFO_Buffer_t *fBuff , ELEMENTS_TYPE items[] , uint32 length)
{
	/* Check if pointer is valid */
	if((fBuff == NULL) || (items == NULL))
	{
		return FIFO_null;
	}

	fBuff->base = items;
	fBuff->head = items;
	fBuff->tail = items;
	fBuff->length = length;
	fBuff->count = 0 ;

	return FIFO_no_error;
}

FIFO_Buffer_Status FIFO_Enqueue(FIFO_Buffer_t *fBuff, ELEMENTS_TYPE *item)
{
	/* Check if FIFO buffer is valid */
	if((fBuff == NULL) || (fBuff->head == NULL) || (fBuff->base == NULL) || (fBuff->tail == NULL))
	{
		return FIFO_null;
	}

	/* Check if buffer is Full */
	if(fBuff->count == fBuff->length)
	{
		printf ("FIFO enqueue failed\n");
		return FIFO_fuLL;
	}

	fBuff->head = item;
	fBuff->count++;

	/*  Check if head reached the end then put it at base
	 *  increase it otherwise */
	if(fBuff->head == (fBuff->base + (fBuff->length * sizeof(ELEMENTS_TYPE))))
	{
		fBuff->head = fBuff->base;
	}
	else
	{
		fBuff->head++;
	}

	return FIFO_no_error;
}

FIFO_Buffer_Status FIFO_Dequeue(FIFO_Buffer_t *fBuff, ELEMENTS_TYPE *item)
{
	/* Check if FIFO buffer is valid */
	if((fBuff == NULL) || (fBuff->head == NULL) || (fBuff->base == NULL) || (fBuff->tail == NULL))
	{
		return FIFO_null;
	}

	/* check if buffer is empty */
	if(fBuff->count == 0)
	{
		return FIFO_empty;
	}

	item = fBuff->tail;
	fBuff->count--;

	/*  Check if tail reached the end then put it at base
	 *  increase it otherwise */
	if (fBuff->tail == (fBuff->base + (fBuff->length) * sizeof(ELEMENTS_TYPE)))
	{
		fBuff->tail = fBuff->base;
	}
	else
	{
		fBuff->tail++;
	}

	return FIFO_no_error;
}

/******************************************************************************
 *  END OF FILE: fifo.c
 ******************************************************************************/
