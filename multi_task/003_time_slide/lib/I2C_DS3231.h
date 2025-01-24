#ifndef _I2C_DS3231_H_
#define _I2C_DS3231_H_
#include "main.h"
typedef struct
{
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
	uint8_t day;
	uint8_t date;
	uint8_t mon;
	uint8_t year;
	uint32_t i2c;
}DateTime;
void rtc_write_time(DateTime *dt);
void rtc_read_time(DateTime *dt);
float rtc_read_temp();
void rtc_init(I2C_HandleTypeDef *i2c);
#endif