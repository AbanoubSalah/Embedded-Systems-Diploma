/**
 * @file lifo.c
 * @brief This file is the implementation to a simple LIFO data structure
 *
 * @author Abanoub Salah
 * @date July 29, 2022
 *
 */

#include <stdio.h>
#include "lifo.h"
#include "platform_types.h"


LIFO_Buffer_Status LIFO_INIT(LIFO_Buffer_t *lBuff , ELEMENTS_TYPE items[] , uint32 length)
{
	/* Check for a valid buffer pointer */
	if((lBuff == NULL) || (lBuff->head == NULL) || (lBuff->base == NULL))
	{
		return LIFO_null;
	}

	lBuff->base = items;
	lBuff->head = items;
	lBuff->length = length;
	lBuff->count = 0 ;

	return LIFO_no_error;
}

LIFO_Buffer_Status LIFO_Push(LIFO_Buffer_t *lBuff, ELEMENTS_TYPE item)
{
	/* Check for a valid buffer pointer */
	if((lBuff == NULL) || (lBuff->head == NULL) || (lBuff->base == NULL))
	{
		return LIFO_null;
	}

	/* Check if buffer is Full */
	if(lBuff->count == lBuff->length)
	{
		return LIFO_fuLL;
	}

	*(lBuff->head) = item;
	lBuff->head++;
	lBuff->count++;

	return LIFO_no_error;
}

LIFO_Buffer_Status LIFO_Pop(LIFO_Buffer_t *lBuff, ELEMENTS_TYPE *item)
{
	/* Check for a valid buffer pointer */
	if(!lBuff || !lBuff->head || !lBuff->base)
	{
		return LIFO_null;
	}

	/* Check if buffer is empty */
	if(lBuff->base == lBuff->head)
	{
		return LIFO_empty;
	}

	(lBuff->head)--;
	*item = *(lBuff->head);
	(lBuff->count)--;

	return LIFO_no_error;
}

LIFO_Buffer_Status LIFO_Print(LIFO_Buffer_t *lBuff)
{
	ELEMENTS_TYPE *tmpELEMENT = lBuff->base;
	sint32 idx;

	/* Check for an empty LIFO */
	if(lBuff->count == 0)
	{
		printf ("\n LIFO is empty\n");

		return LIFO_empty;
	}

	/* Prints out FIFO contents */
	printf ("\n\n ======FIFO_Print=======\n ");
	for(idx = 0; idx < lBuff->count; ++idx)
	{
		printf ("%d, ", *tmpELEMENT);
		++tmpELEMENT;
	}
	printf ("\n =======================\n\n");

	return LIFO_no_error;
}
