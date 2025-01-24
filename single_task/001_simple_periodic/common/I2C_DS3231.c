/*  original author:  Pham Huy Tuyen<huytuyen2306@gmail.com>
    copyright Pham Huy Tuyen, 2024
		------------------------------------
		huong dan su dung:
		- Khai bao I2C
		- Khai bao truoc main DateTime date_time;
		- Khoi tao rtc_init()
		- Khoi tao thoi gian gui den DS3231
		      +date_time.hour = 
          +date_time.min = 
	        +date_time.sec =
	        +date_time.day =
	        +date_time.date = 
	        +date_time.mon =
	        +date_time.year =
		- Gui thoi gian rtc_write_time(&date_time);
		- Doc thoi gian rtc_read_time(&date_time);
		- Doc nhiet do rtc_red_temp();
		-------------------------------------
*/

#include "I2C_DS3231.h"
#define RTC_ADDRESS (0x68<<1) // do dia chi cua module ds3231 la 7 bit , bit 0 o cuoi la bit write
//cach 1
//extern I2C_HandleTypeDef hi2c1;
//cach 2
 static I2C_HandleTypeDef *ds_i2c; // bien static tuc la chi dung trong file nay
uint8_t Decimal2BCD(uint8_t num){
  return (num/10)<<4 | (num%10);
}
uint8_t BCD2Decimal(uint8_t num){
  return (num>>4)*10 + (num&0x0F);
}
// ghi du lieu
void rtc_write_time(DateTime *dt){
	uint8_t data[8];
	data[0]=0x00;
	data[1]= Decimal2BCD(dt->sec);
	data[2]= Decimal2BCD(dt->min);
	data[3]= Decimal2BCD(dt->hour);
	data[4]= Decimal2BCD(dt->day);
	data[5]= Decimal2BCD(dt->date);
	data[6]= Decimal2BCD(dt->mon);
	data[7]= Decimal2BCD(dt->year);
	HAL_I2C_Master_Transmit(ds_i2c,RTC_ADDRESS,data,8,100);
}
// doc du lieu
void rtc_read_time(DateTime *dt){
	uint8_t data[7];
	uint8_t add_reg=0x00; // dia chi cua thanh ghi cua slave ma master muon doc du lieu
	HAL_I2C_Master_Transmit(ds_i2c,RTC_ADDRESS,&add_reg,1,100); // gui dia chi thanh ghi ma master muon doc du lieu
	HAL_I2C_Master_Receive(ds_i2c,RTC_ADDRESS,data,7,100); // doc du lieu
	dt->sec= BCD2Decimal(data[0]);
	dt->min= BCD2Decimal(data[1]);
	dt->hour= BCD2Decimal(data[2]);
	dt->day= BCD2Decimal(data[3]);
	dt->date= BCD2Decimal(data[4]);
	dt->mon= BCD2Decimal(data[5]);
	dt->year= BCD2Decimal(data[6]);
}
// doc nhiet do
float rtc_read_temp(){
	uint8_t data[2];
	float temperarate;
	uint8_t add_reg=0x11; // dia chi cua thanh ghi cua slave ma master muon doc du lieu
	HAL_I2C_Master_Transmit(ds_i2c,RTC_ADDRESS,&add_reg,1,100); // gui dia chi thanh ghi ma master muon doc du lieu
	HAL_I2C_Master_Receive(ds_i2c,RTC_ADDRESS,data,2,100); // doc du lieu
	if(data[1]==0x00) temperarate=0;
	else if (data[1]==0x40) temperarate=0.25;
	else if(data[1]==0x80) temperarate=0.5;
	else temperarate=0.75;
	return data[0]+temperarate; 
}
void rtc_init(I2C_HandleTypeDef *i2c){
  ds_i2c=i2c;
}