#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int pipes[2][2];
    pid_t children[3];
    if (pipe(pipes[0]) < 0) { perror("pipe"); return 1; }
    if (pipe(pipes[1]) < 0) {
        perror("pipe"); close(pipes[0][0]); close(pipes[0][1]); return 1;
    }
    char *commands[3][4] = {
        {"ls", "/usr/bin", NULL, NULL},
        {"grep", "x", NULL, NULL},
        {"wc", "-l", NULL, NULL}
    };
    int count = 0, failed = 0;
    for (int stage = 0; stage < 3; stage++) {
        pid_t pid = fork();
        if (pid < 0) { perror("fork"); failed = 1; break; }
        if (pid == 0) {
            if (stage > 0 && dup2(pipes[stage - 1][0], 0) < 0) {
                perror("dup2"); _exit(1);
            }
            if (stage < 2 && dup2(pipes[stage][1], 1) < 0) {
                perror("dup2"); _exit(1);
            }
            for (int i = 0; i < 2; i++) {
                close(pipes[i][0]); close(pipes[i][1]);
            }
            execvp(commands[stage][0], commands[stage]);
            perror("exec"); _exit(127);
        }
        children[count++] = pid;
    }
    for (int i = 0; i < 2; i++) {
        close(pipes[i][0]); close(pipes[i][1]);
    }
    for (int i = 0; i < count; i++) {
        int status;
        if (waitpid(children[i], &status, 0) < 0) { perror("waitpid"); failed = 1; }
        else if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) failed = 1;
    }
    return failed;
}
