/*
 * queue.c
 *
 *  Created on: Jan 22, 2025
 *      Author: Admin
 */
#include <stdbool.h>
#include "queue.h"
void init_event_queue(EventQueue *queue) {
    queue->begin = 0;
    queue->end = 0;
    queue->count = 0;
}

bool enqueue_event(EventQueue *queue, EventType event) {
    if (queue->count < MAX_EVENTS) {
        queue->events[queue->end] = event;
        queue->end = (queue->end + 1) % MAX_EVENTS;
        queue->count++;
        return true;
    }
    return false;
}

bool dequeue_event(EventQueue *queue, EventType *event) {
    if (queue->count > 0) {
        *event = queue->events[queue->begin];
        queue->begin = (queue->begin + 1) % MAX_EVENTS;
        queue->count--;
        return true;
    }
    return false;
}
