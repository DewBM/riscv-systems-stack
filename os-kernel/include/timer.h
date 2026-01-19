#ifndef TIMER_H
#define TIMER_H

#define CLINT_BASE     0x02000000
#define CLINT_MTIME    (CLINT_BASE + 0xBFF8)
#define CLINT_MTIMECMP (CLINT_BASE + 0x4000)

void reset_timer();

#endif
