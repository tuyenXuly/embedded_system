#ifndef TASK_CONFIG_TYPE_H
#define TASK_CONFIG_TYPE_H

#include <stdlib.h>

typedef struct {
    uint16_t perious;
    uint16_t execution_time;
    uint16_t deadline;
    uint16_t priority;
    uint16_t global_cycle;
} TaskConfig;

#endif // TASK_CONFIG_H
