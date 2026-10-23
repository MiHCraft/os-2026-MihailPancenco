#include "kernel/types.h"
#include "user/user.h"

/* One filter per prime. Mark noreturn so recursive process creation is clear. */
static void filter(int input) __attribute__((noreturn));

static void
filter(int input)
{
  int prime, value, p[2];
  int n = read(input, &prime, sizeof(prime));
  if(n == 0){ close(input); exit(0); }
  if(n != sizeof(prime)){ fprintf(2, "primes: read failed\n"); exit(1); }
  printf("prime %d\n", prime);
  if(pipe(p) < 0){ fprintf(2, "primes: pipe failed\n"); exit(1); }
  int pid = fork();
  if(pid < 0){ fprintf(2, "primes: fork failed\n"); exit(1); }
  if(pid == 0){ close(input); close(p[1]); filter(p[0]); }
  close(p[0]);
  while((n = read(input, &value, sizeof(value))) == sizeof(value)){
    if(value % prime && write(p[1], &value, sizeof(value)) != sizeof(value)){
      fprintf(2, "primes: write failed\n"); exit(1);
    }
  }
  close(input); close(p[1]);
  int status;
  if(wait(&status) < 0 || status != 0 || n != 0)
    exit(1);
  exit(0);
}

int
main(int argc, char *argv[])
{
  int p[2];
  if(pipe(p) < 0){ fprintf(2, "primes: pipe failed\n"); exit(1); }
  int pid = fork();
  if(pid < 0){ fprintf(2, "primes: fork failed\n"); exit(1); }
  if(pid == 0){ close(p[1]); filter(p[0]); }
  close(p[0]);
  for(int value = 2; value <= 35; value++)
    if(write(p[1], &value, sizeof(value)) != sizeof(value)){
      fprintf(2, "primes: write failed\n"); exit(1);
    }
  close(p[1]);
  int status;
  if(wait(&status) < 0 || status != 0)
    exit(1);
  exit(0);
}
