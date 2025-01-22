/*
 * task.h
 *
 *  Created on: Jan 19, 2025
 *      Author: Pham Huy Tuyen
 *
 */

#ifndef TASK_TYPE_H_
#define TASK_TYPE_H_

#include <stdbool.h>
typedef struct {
    void (*task_fn)(void);  // Function pointer
    bool active;            // State of function | 1 or 0
} Task;


#endif /* TASK_TYPE_H_ */
