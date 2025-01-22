#ifndef __CLI_TYPE_H__
#define __CLI_TYPE_H__
#include <stdint.h>

typedef void (*cli_command_func_t)(char **argv,uint8_t argv_num);
typedef struct{
  char *cmd_name;
	cli_command_func_t func;
	char *help;
}cli_command_t;

#endif