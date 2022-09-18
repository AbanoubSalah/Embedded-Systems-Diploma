/******************************************************************************
 * @file platform_types.h
 * @brief This file is the platform data types definitions
 *
 * @author Abanoub Salah
 * @date September 17, 2022
 * ****************************************************************************/

#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

#include <stdbool.h>
#include <stdint.h>

/*- CONSTANTS ----------------------------------------------*/
#define WORD_LENGTH_BITS         (32u)
#define WORD_LENGTH_BYTES        (4u)
#define MSB_FIRST                (0u)    /* big endian bit ordering */
#define LSB_FIRST                (1u)    /* little endian bit ordering */

#define HIGH_BYTE_FIRST          (0u)    /* big endian byte ordering */
#define LOW_BYTE_FIRST           (1u)    /* little endian byte ordering */

#ifndef TRUE
   #define TRUE                  (1u)
#endif

#ifndef FALSE
   #define FALSE                 (0u)
#endif

#define CPU_BIT_ORDER            LSB_FIRST        /*little endian bit ordering*/
#define CPU_BYTE_ORDER           LOW_BYTE_FIRST   /*little endian byte ordering*/

typedef _Bool               boolean;
typedef int8_t              sint8;
typedef uint8_t             uint8;
typedef char				char_t;
typedef int16_t             sint16;
typedef uint16_t            uint16;
typedef int32_t             sint32;
typedef uint32_t            uint32;
typedef int64_t             sint64;
typedef uint64_t            uint64;


typedef volatile int8_t     vint8;
typedef volatile uint8_t    vuint8;

typedef volatile int16_t    vint16;
typedef volatile uint16_t   vuint16;

typedef volatile int32_t    vint32;
typedef volatile uint32_t   vuint32;

typedef volatile int64_t    vint64;
typedef volatile uint64_t   vuint64;

#endif  /* PLATFORM_TYPES_H_ */

/**********************************************************************************************************************
 *  END OF FILE: platform_types.h
 *********************************************************************************************************************/

