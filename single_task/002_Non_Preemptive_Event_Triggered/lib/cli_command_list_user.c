#include <function_cli.h>
#include "cli_type.h"
#include <stddef.h>
cli_command_t list_command[]={
   {"task1",update_task1,"task1 : read temperature and humidity"},
   {"task2",update_task2,"task2 : read DS3231"},
   {"task3",update_task3,"task3 : send time,data and temperature,humidity to COM"},
   {"task4",update_task4,"task5 : send time,data and temperature,humidity LCD"},
   {"frame",data_frame,"frame : give data of frame"},
   {"data",data_task,"data : give data of tasks"},
   {"help",help,"help : give data of all function"},
   {"info",info,"info : info of parameter"},
   {NULL , NULL , NULL}
};
