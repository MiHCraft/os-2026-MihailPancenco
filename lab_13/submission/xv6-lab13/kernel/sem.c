#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "spinlock.h"

#define NSEM 8
#define SEM_VALUE_MAX 0x7fffffff

struct sem {
  struct spinlock lock;
  int value;
};

static struct sem sems[NSEM];

void
seminit(void)
{
  for (int id = 0; id < NSEM; id++)
    initlock(&sems[id].lock, "sem");
}

uint64
sys_sem_init(void)
{
  int id, value;

  argint(0, &id);
  argint(1, &value);
  if (id < 0 || id >= NSEM || value < 0)
    return -1;

  struct sem *s = &sems[id];
  acquire(&s->lock);
  s->value = value;
  if (value > 0)
    wakeup(s);
  release(&s->lock);
  return 0;
}

uint64
sys_sem_down(void)
{
  int id;
  argint(0, &id);
  if (id < 0 || id >= NSEM)
    return -1;

  struct sem *s = &sems[id];
  acquire(&s->lock);
  while (s->value == 0) {
    sleep_prepare(s);
    release(&s->lock);
    sleep_interruptible();
    if (killed(myproc()))
      return -1;
    acquire(&s->lock);
  }
  s->value--;
  release(&s->lock);
  return 0;
}

uint64
sys_sem_up(void)
{
  int id;
  argint(0, &id);
  if (id < 0 || id >= NSEM)
    return -1;

  struct sem *s = &sems[id];
  acquire(&s->lock);
  if (s->value == SEM_VALUE_MAX) {
    release(&s->lock);
    return -1;
  }
  s->value++;
  wakeup(s);
  release(&s->lock);
  return 0;
}

uint64
sys_sem_trydown(void)
{
  int id;
  argint(0, &id);
  if (id < 0 || id >= NSEM)
    return -1;

  struct sem *s = &sems[id];
  acquire(&s->lock);
  if (s->value == 0) {
    release(&s->lock);
    return -1;
  }
  s->value--;
  release(&s->lock);
  return 0;
}
