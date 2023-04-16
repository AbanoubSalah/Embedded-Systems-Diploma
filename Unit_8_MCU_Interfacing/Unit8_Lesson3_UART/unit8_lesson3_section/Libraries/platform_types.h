/*******************************************************************************
 * @file platform_types.h
 * @brief This file is the platform data types definitions
 *
 * @author Abanoub Salah
 * @date September 13, 2022
 ******************************************************************************/

#ifndef LIBRARIES_PLATFORM_TYPES_H_
#define LIBRARIES_PLATFORM_TYPES_H_

#include <stdbool.h>
#include <stdint.h>

/* CONSTANTS */
#define WORD_LENGTH_BITS        (32U)
#define WORD_LENGTH_BYTES       (4U)
#define MSB_FIRST               (0U)    /* big endian bit ordering */
#define LSB_FIRST               (1U)    /* little endian bit ordering */

#define HIGH_BYTE_FIRST         (0U)    /* big endian byte ordering */
#define LOW_BYTE_FIRST          (1U)    /* little endian byte ordering */

#ifndef TRUE
   #define TRUE                 (1U)
#endif

#ifndef FALSE
   #define FALSE                (0U)
#endif

#define CPU_BIT_ORDER           LSB_FIRST        /*little endian bit ordering*/
#define CPU_BYTE_ORDER          LOW_BYTE_FIRST   /*little endian byte ordering*/

#define LOW						(0U)
#define HIGH					(1U)

typedef _Bool					boolean;
typedef int8_t              	sint8_t;
typedef uint8_t             	uint8_t;
typedef char					char_t;
typedef int16_t             	sint16_t;
typedef uint16_t            	uint16_t;
typedef int32_t             	sint32_t;
typedef uint32_t            	uint32_t;
typedef int64_t             	sint64_t;
typedef uint64_t            	uint64_t;


typedef volatile int8_t     	vint8_t;
typedef volatile uint8_t    	vuint8_t;

typedef volatile int16_t    	vint16_t;
typedef volatile uint16_t   	vuint16_t;

typedef volatile int32_t    	vint32_t;
typedef volatile uint32_t   	vuint32_t;

typedef volatile int64_t    	vint64_t;
typedef volatile uint64_t   	vuint64_t;

#ifndef NULL
#define NULL                 	((void *) 0)
#endif

#endif  /* LIBRARIES_PLATFORM_TYPES_H_ */

/******************************************************************************
 *  END OF FILE: platform_types.h
 ******************************************************************************/
