/* Build: gcc -Wall -Wextra -Werror -o syscalls syscalls.c */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int
main(void)
{
    const char msg[] = "hello, kernel\n";
    const size_t length = sizeof(msg) - 1;
    char buf[64];
    ssize_t n;

    int fd = open("note.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) { perror("open for writing"); return 1; }
    printf("open returned descriptor %d\n", fd);

    do { n = write(fd, msg, length); } while (n < 0 && errno == EINTR);
    if (n < 0) { perror("write"); close(fd); return 1; }
    if ((size_t)n != length) {
        fputs("short write\n", stderr);
        close(fd);
        return 1;
    }
    printf("write sent %zd bytes\n", n);
    if (close(fd) < 0) { perror("close after writing"); return 1; }

    fd = open("note.txt", O_RDONLY);
    if (fd < 0) { perror("open for reading"); return 1; }
    do { n = read(fd, buf, sizeof(buf) - 1); } while (n < 0 && errno == EINTR);
    if (n < 0) { perror("read"); close(fd); return 1; }
    if ((size_t)n != length || memcmp(buf, msg, length) != 0) {
        fputs("unexpected file contents\n", stderr);
        close(fd);
        return 1;
    }
    buf[n] = '\0';
    printf("read got %zd bytes: %s", n, buf);
    if (close(fd) < 0) { perror("close after reading"); return 1; }
    return 0;
}
