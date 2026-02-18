#ifndef TASK_H
#define TASK_H

#include <stdint.h>

#define MAX_TASKS 4
#define STACK_SIZE 1024

struct Task {
    uint32_t *sp;
    int id;
};

extern struct Task task_list[MAX_TASKS];
extern uint8_t stack_list[MAX_TASKS][STACK_SIZE];

extern int current_task;
extern int num_tasks;


void task_create(void(*task_function)(void));

#endif
