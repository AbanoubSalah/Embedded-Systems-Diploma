/**
 * @file main.c
 * @brief Main entry point to the LIFO driver
 *
 * This file contains the main code for LIFO driver.
 *
 * @author Abanoub Salah
 * @date July 29, 2022
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "lifo.h"
#include "platform_types.h"

int main()
{
	ELEMENTS_TYPE staticBuffer [LIFO_BUFFER_LENGTH];
	ELEMENTS_TYPE tmpELEMENT;
	LIFO_Buffer_t buffer;
	uint32 idx;

	LIFO_INIT(&buffer, staticBuffer, LIFO_BUFFER_LENGTH);

	printf ( "\n buffer (static allocation) LIFO_Push = " );
	for(idx = 0; idx < LIFO_BUFFER_LENGTH; ++idx)
	{
		printf(" %d,", idx);
		LIFO_Push(&buffer, idx);
	}

	LIFO_Print(&buffer);

	printf("\n buffer (static allocation) LIFO_Pop = ");
	for (idx = 0; idx < LIFO_BUFFER_LENGTH; ++idx)
	{
		LIFO_Pop(&buffer, &tmpELEMENT);
		printf(" %d,", tmpELEMENT);
	}

	LIFO_Print(&buffer);

	return EXIT_SUCCESS;
}
