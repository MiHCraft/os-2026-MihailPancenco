CC = gcc
CFLAGS = -std=c11 -D_POSIX_C_SOURCE=200809L -Wall -Wextra -Werror -O2
PROGRAMS = run run_date run_missing zombie redirect pipeline pipeline3

.PHONY: all clean
all: $(PROGRAMS)
%: %.c
	$(CC) $(CFLAGS) -o $@ $<
clean:
	rm -f $(PROGRAMS) out.txt
