#ifndef BSP_H_
#define BSP_H_


#include "def.h"


#define BOARD_FLASH_SIZE        (2*1024*1024)


#include "config/board/clock_config.h"
#include "config/board/peripherals.h"
#include "config/board/pin_mux.h"

#include "fsl_common.h"
#include "fsl_gpio.h"


void logPrintf(const char *fmt, ...);



bool bspInit(void);

void delay(uint32_t time_ms);
uint32_t millis(void);



#endif