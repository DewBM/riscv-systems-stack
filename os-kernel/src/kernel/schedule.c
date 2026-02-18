#include "../../include/schedule.h"
#include "../../include/task.h"
#include "../../include/uart.h"

uint32_t *schedule(uint32_t *current_sp) {
    task_list[current_task].sp = current_sp;

    current_task = (current_task + 1) % num_tasks;

    return task_list[current_task].sp;
}
