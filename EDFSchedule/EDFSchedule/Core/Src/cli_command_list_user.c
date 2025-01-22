#include <function_cli.h>
#include "cli_type.h"
#include <stddef.h>
cli_command_t list_command[]={
   {"task1,",update_task1,"task1 : read temperature and humidity"},
   {"task2,",update_task2,"task2 : read DS3231"},
   {"task3,",update_task3,"task3 : send temperature and humidity to LCD"},
   {"task4,",update_task4,"task5 : send time, date to LCD"},
   {"frame,",data_frame,"frame : give data frame"},
   {"help,",help,"help : give data all function"},
   {"info,",info,"info : info of parameter"},
   {NULL , NULL , NULL}
};

