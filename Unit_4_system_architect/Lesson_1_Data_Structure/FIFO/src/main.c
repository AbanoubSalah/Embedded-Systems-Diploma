/**
 * @file main.c
 * @brief Main entry point to the FIFO driver
 *
 * This file contains the main code for FIFO driver.
 *
 * @author Abanoub Salah
 * @date July 29, 2022
 *
 */

#include <fifo.h>
#include <stdio.h>
#include <stdlib.h>
#include "platform_types.h"

int main()
{
	ELEMENTS_TYPE StaticBuffer [FIFO_BUFFER_LENGTH];
	ELEMENTS_TYPE tmpELEMENT;
	FIFO_Buffer_t buffFIFO;
	uint32 idx;

	/* Check for a successful initiation */
	if(FIFO_INIT(&buffFIFO, StaticBuffer, FIFO_BUFFER_LENGTH) == FIFO_no_error)
	{
		printf ("FIFO Initialization Done\n\n");
	}

	/* Try to enqueue more than FIFIO length */
	for(tmpELEMENT = 0; tmpELEMENT < FIFO_BUFFER_LENGTH + 2; ++tmpELEMENT)
	{
		printf ("FIFO Enqueue (%x) \n", tmpELEMENT);
		if(FIFO_Enqueue(&buffFIFO , &tmpELEMENT)== FIFO_no_error)
		{
			printf ("FIFO Enqueue (%x) DONE \n", tmpELEMENT);
		}
		else
		{
			printf ("FIFO Enqueue (%x) Failed \n", tmpELEMENT);
		}
	}

	FIFO_Print(&buffFIFO);

	/* Dequeuing most of FIFO then print it */
	for(idx = 0; idx < FIFO_BUFFER_LENGTH - 2; ++idx)
	{
		FIFO_Dequeue(&buffFIFO, &tmpELEMENT);
		printf("FIFO Dequeue : Data = %x\n", tmpELEMENT);
	}

	FIFO_Print(&buffFIFO);

	return EXIT_SUCCESS;
}
