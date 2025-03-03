#include "function_cli.h"
#include <stdint.h>
#include "print_cli.h"
#include <stdlib.h>
#include "task_config_type.h"
#include "cli_type.h"
#include "stdio.h"
#include "main.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;


extern cli_command_t list_command[];

void update_task1(char **argv,uint8_t argv_num){
	//Update only if the parameter is not -1
	    HAL_TIM_Base_Stop_IT(&htim1);
	    HAL_TIM_Base_Stop_IT(&htim2);
	    HAL_TIM_Base_Stop_IT(&htim3);
	    HAL_TIM_Base_Stop_IT(&htim4);
	    if(atoi(argv[1]) != -1 ){
	     	if(atoi(argv[2]) == -1 )
	     		htim1.Init.Period = atoi(argv[1])*(HAL_RCC_GetPCLK2Freq()/htim1.Init.Prescaler)/1000-1;
	     	else
	     		htim1.Init.Period = atoi(argv[1])*(HAL_RCC_GetPCLK2Freq()/atoi(argv[2]))/1000-1;

	     	print_cli("update task1 successfully : %u\n",htim1.Init.Period);
	     }
	    if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
	    {
	        Error_Handler();
	    }
	    HAL_TIM_Base_Start_IT(&htim1);
	    HAL_TIM_Base_Start_IT(&htim2);
	    HAL_TIM_Base_Start_IT(&htim3);
	    HAL_TIM_Base_Start_IT(&htim4);
	}
void update_task2(char **argv,uint8_t argv_num){
    HAL_TIM_Base_Stop_IT(&htim1);
    HAL_TIM_Base_Stop_IT(&htim2);
    HAL_TIM_Base_Stop_IT(&htim3);
    HAL_TIM_Base_Stop_IT(&htim4);
    if(atoi(argv[1]) != -1 ){
     	if(atoi(argv[2]) == -1 )
     		htim2.Init.Period = atoi(argv[1])*(HAL_RCC_GetPCLK2Freq()/htim2.Init.Prescaler)/1000-1;
     	else
     		htim2.Init.Period = atoi(argv[1])*(HAL_RCC_GetPCLK2Freq()/atoi(argv[2]))/1000-1;
     	print_cli("update task2 successfully : %u\n",htim2.Init.Period);
     }
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_TIM_Base_Start_IT(&htim1);
    HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_Base_Start_IT(&htim4);
}
void update_task3(char **argv,uint8_t argv_num){
    HAL_TIM_Base_Stop_IT(&htim1);
    HAL_TIM_Base_Stop_IT(&htim2);
    HAL_TIM_Base_Stop_IT(&htim3);
    HAL_TIM_Base_Stop_IT(&htim4);
    if(atoi(argv[1]) != -1 ){
     	if(atoi(argv[2]) == -1 )
     		htim3.Init.Period = atoi(argv[1])*(HAL_RCC_GetPCLK2Freq()/htim3.Init.Prescaler)/1000-1;
     	else
     		htim3.Init.Period = atoi(argv[1])*(HAL_RCC_GetPCLK2Freq()/atoi(argv[2]))/1000-1;

     	print_cli("update task3 successfully : %u\n",htim3.Init.Period);
     }
    if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_TIM_Base_Start_IT(&htim1);
    HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_Base_Start_IT(&htim4);
}
void update_task4(char **argv,uint8_t argv_num){
    HAL_TIM_Base_Stop_IT(&htim1);
    HAL_TIM_Base_Stop_IT(&htim2);
    HAL_TIM_Base_Stop_IT(&htim3);
    HAL_TIM_Base_Stop_IT(&htim4);
    if(atoi(argv[1]) != -1 ){
    	if(atoi(argv[2]) == -1 )
    		htim4.Init.Period = atoi(argv[1])*(HAL_RCC_GetPCLK2Freq()/htim4.Init.Prescaler)/1000-1;
    	else
    		htim4.Init.Period = atoi(argv[1])*(HAL_RCC_GetPCLK2Freq()/atoi(argv[2]))/1000-1;
    	print_cli("update task4 successfully : %u\n",htim4.Init.Period);
    }
    if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_TIM_Base_Start_IT(&htim1);
    HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_Base_Start_IT(&htim4);
}
void data_frame(char **argv,uint8_t argv_num){
	print_cli("task-id | perious | prescaler\n");
}

void help(char **argv,uint8_t argv_num){
	uint8_t i = 0;
	while(list_command[i].help != NULL){
		print_cli("%s \n",list_command[i].help);
		i++;
	}
}

void data_task(char **argv,uint8_t argv_num){
	print_cli("task 1 - Period: %s , Prescaler: %s\n",htim1.Init.Period,htim1.Init.Prescaler);
	print_cli("task 2 - Period: %s , Prescaler: %s\n",htim2.Init.Period,htim2.Init.Prescaler);
	print_cli("task 3 - Period: %s , Prescaler: %s\n",htim3.Init.Period,htim3.Init.Prescaler);
	print_cli("task 4 - Period: %s , Prescaler: %s\n",htim4.Init.Period,htim4.Init.Prescaler);

}
void info(char **argv,uint8_t argv_num){
	print_cli("The unit of time is miliseconds (ms).\n");
	print_cli("Set -1 if you dont want to change that parameter.\n");
}
