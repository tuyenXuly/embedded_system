#ifndef __UART_H__
#define __UART_H__
#include "main.h"
#include "stdint.h"
#include <string.h>
void uart_handel(void);
void uart_init(UART_HandleTypeDef *huart);
#endif
