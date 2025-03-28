#ifndef _PARAMS_H
#define _PARAMS_H

#include <string.h>

#include "stm32u5xx_hal.h"

//#define FLASH_PAGE_SIZE		(uint32_t) ( 2048 )

struct params
{
    struct
    {
        unsigned int major;
        unsigned int minor;
        unsigned int to_major;
        unsigned int to_minor;
        unsigned int size;
        unsigned int crc;
    } version;

    unsigned int gap[2038];
//    unsigned int crc;
    uint32_t crc;
    uint32_t align_crc[3];
};

void params_init( void );
void params_check_for_changes( void );

#define ASSERT_CONCAT_(a, b) a##b
#define ASSERT_CONCAT(a, b) ASSERT_CONCAT_(a, b)
#define ct_assert(e) enum { ASSERT_CONCAT(assert_line_, __LINE__) = 1/(!!(e)) }

#endif
