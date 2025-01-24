#include "uart.h"
#include "command_excute.h"
#define BUFFER_DATA 128
static UART_HandleTypeDef *uart;
uint8_t data_rx;
uint8_t buff_rx[BUFFER_DATA];
uint8_t index_rx=0;
uint8_t flag_rx=0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
   if(huart->Instance == uart->Instance){
	    buff_rx[index_rx++]=data_rx;
		  if(data_rx == '\n'){
			  data_rx=1;
			  flag_rx=1;
			}
	 HAL_UART_Receive_IT(uart,&data_rx,1);
	 }
 
 }
void uart_handel(){
  if(flag_rx==1){
		command_excute((char *)buff_rx,index_rx);
		memset(buff_rx,0,index_rx);
		index_rx=0;
		flag_rx=0;
	}
}
void uart_init(UART_HandleTypeDef *huart){
	uart = huart;
  HAL_UART_Receive_IT(uart,&data_rx,1);
}
