#include "../../include/timer.h"

volatile unsigned long *mtime = (unsigned long*)CLINT_MTIME;
volatile unsigned long *mtimecmp = (unsigned long*)CLINT_MTIMECMP;

void reset_timer() {
    *mtimecmp = *mtime + 50000000;
}
