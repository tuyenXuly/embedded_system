#include "command_excute.h"
#include "print_cli.h"
#include "function_cli.h"
#include <stdlib.h>
#include "cli_type.h"
extern UART_HandleTypeDef huart1;
extern cli_command_t list_command[];
cli_command_t* find_command_from_list(char *cmd)
{
	uint8_t i=0;
  while(list_command[i].cmd_name != NULL){
	   if(strcmp(list_command[i].cmd_name,cmd) ==0){
		    return &list_command[i];
		 }
		 i++;
	}
	return NULL;
}

void command_excute(char *buff,uint8_t len){
  char *token=strtok(buff," ");
	char *argv[10];
	uint8_t num_arg=0;
  while(token){
    argv[num_arg++]=token;
	  token=strtok(NULL," ");
	}
 cli_command_t* command =find_command_from_list(argv[0]);
	if(command == NULL){
	  print_cli("command not found!");
	}
	else{
	  return command->func(argv,num_arg);
	}
}
