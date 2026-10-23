#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int p[2];
    if (pipe(p) < 0) { perror("pipe"); return 1; }
    pid_t producer = fork();
    if (producer < 0) { perror("fork"); close(p[0]); close(p[1]); return 1; }
    if (producer == 0) {
        close(1);
        if (dup(p[1]) < 0) { perror("dup"); _exit(1); }
        close(p[0]);
        close(p[1]);
        execlp("ls", "ls", "/etc", (char *)NULL);
        perror("exec ls");
        _exit(127);
    }
    pid_t consumer = fork();
    if (consumer < 0) {
        perror("fork"); close(p[0]); close(p[1]);
        waitpid(producer, NULL, 0); return 1;
    }
    if (consumer == 0) {
        close(0);
        if (dup(p[0]) < 0) { perror("dup"); _exit(1); }
        close(p[0]);
        close(p[1]);
        execlp("wc", "wc", "-l", (char *)NULL);
        perror("exec wc");
        _exit(127);
    }
    close(p[0]); /* The parent uses neither end. */
    close(p[1]); /* Closing the last writer is necessary for EOF. */
    int a, b;
    if (waitpid(producer, &a, 0) < 0) { perror("waitpid"); return 1; }
    if (waitpid(consumer, &b, 0) < 0) { perror("waitpid"); return 1; }
    return !(WIFEXITED(a) && WEXITSTATUS(a) == 0 &&
             WIFEXITED(b) && WEXITSTATUS(b) == 0);
}
