#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  int empty, available, consumed;

  if (sem_init(4, 0) < 0)
    exit(1);
  empty = sem_trydown(4);
  if (sem_up(4) < 0)
    exit(1);
  available = sem_trydown(4);
  consumed = sem_trydown(4);
  printf("empty: %d, after up: %d, consumed: %d\n",
         empty, available, consumed);
  if (empty != -1 || available != 0 || consumed != -1 ||
      sem_init(-1, 0) != -1 || sem_init(4, -1) != -1 ||
      sem_down(8) != -1 || sem_up(8) != -1 || sem_trydown(8) != -1 ||
      sem_init(4, 0x7fffffff) != 0 || sem_up(4) != -1)
    exit(1);
  printf("semtry: OK\n");
  exit(0);
}
