#include "../../include/task.h"
#include "../../include/uart.h"

struct Task task_list[MAX_TASKS];
uint8_t stack_list[MAX_TASKS][STACK_SIZE];

int current_task = 0;
int num_tasks = 0;

// when creating a new task, point its sp to the address of the function to begin from
void task_create(void (*task_function)(void)) {
    struct Task *task = &task_list[num_tasks];

    uint32_t *sp = (uint32_t *)(stack_list[num_tasks] + STACK_SIZE);

    *(--sp) = (uint32_t)task_function;

    task->sp = sp;
    task->id = num_tasks;

    num_tasks++;
}
