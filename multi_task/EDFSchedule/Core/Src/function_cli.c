#include "function_cli.h"
#include <stdint.h>
#include "print_cli.h"
#include <stdlib.h>
#include "task_config_type.h"
#include "cli_type.h"
#include "stdio.h"

extern TaskConfig task1_parameter;
extern TaskConfig task2_parameter;
extern TaskConfig task3_parameter;
extern TaskConfig task4_parameter;

extern cli_command_t list_command[];

void update_task1(char **argv,uint8_t argv_num){
	//Update only if the parameter is not -1
//	if (atoi(argv[1]) != -1) {
//	        task1_parameter.perious = atoi(argv[1]);
//	    }
//	    if (atoi(argv[2]) != -1) {
//	        task1_parameter.execution_time = atoi(argv[2]);
//	    }
//	    if (atoi(argv[3]) != -1) {
//	        task1_parameter.deadline = atoi(argv[3]);
//	    }
//	    if (atoi(argv[4]) != -1) {
//	        task1_parameter.priority = atoi(argv[4]);
//	    }
//	    if (atoi(argv[5]) != -1) {
//	        task1_parameter.global_cycle = atoi(argv[5]);
//	    }
//
//	    printf("perious : %d execution_time : %d deadline : %d priority : %d global_cycle : %d\n",
//	           task1_parameter.perious, task1_parameter.execution_time, task1_parameter.deadline,
//	           task1_parameter.priority, task1_parameter.global_cycle);

	    print_cli("update task1 successfully\n");
	}
void update_task2(char **argv,uint8_t argv_num){

}
void update_task3(char **argv,uint8_t argv_num){

}
void update_task4(char **argv,uint8_t argv_num){

}
void data_frame(char **argv,uint8_t argv_num){
	print_cli("task-id | perious | execution_time | deadline | priority | global-cycle");
}

void help(char **argv,uint8_t argv_num){
	uint8_t i = 0;
	while(list_command[i].help != NULL){
		print_cli("%s \n",list_command[i].help);
		i++;
	}
}

void info(char **argv,uint8_t argv_num){
	print_cli("The unit of time is milliseconds (ms).\n");
	print_cli("Set -1 if you dont want to change that parameter.\n");
}
