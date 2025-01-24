#include "print_cli.h"
#include "main.h"
#include "stdarg.h"
#include "stdio.h"
extern UART_HandleTypeDef huart1;

void print_cli(const char* str, ...)
{
  char stringArray[128];
	
	va_list args;
	va_start(args,str);
	uint8_t len_str = vsprintf(stringArray,str,args);
	va_end(args);
	
	HAL_UART_Transmit(&huart1,(uint8_t *)stringArray,len_str,200);
}
