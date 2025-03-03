/*
 * queue.h
 *
 *  Created on: Jan 22, 2025
 *      Author: Admin
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#define MAX_EVENTS 10

typedef enum {
	EVENT_TIMER1,
    EVENT_TIMER2,
    EVENT_TIMER3,
	EVENT_TIMER4,
    EVENT_NONE
} EventType;

typedef struct {
    EventType events[MAX_EVENTS];
    int begin;
    int end;
    int count;
} EventQueue;

void init_event_queue(EventQueue *queue);
bool enqueue_event(EventQueue *queue, EventType event);
bool dequeue_event(EventQueue *queue, EventType *event);

#endif /* QUEUE_H_ */
