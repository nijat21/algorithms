#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
    The version of ft_peopen manipulating fds in parent.
*/

int ft_popen(const char *file, char *const argv[], char type) {
    int fds[2];
    pid_t pid;
    int out_backup = dup(STDOUT_FILENO);
    int in_backup = dup(STDIN_FILENO);

    if (!file || !argv || !(type == 'r' || type == 'w'))
        return -1;
    if (pipe(fds) == -1)
        return -1;
    pid = fork();
    if (pid == -1) {
        close(fds[0]);
        close(fds[1]);
        return -1;
    }
    if (type == 'r') {
        if (dup2(fds[1], STDOUT_FILENO) == -1) {
            return -1;
        }
    } else {
        if (dup2(fds[0], STDIN_FILENO) == -1) {
            return -1;
        }
    }
    if (pid == 0) {
        close(fds[0]);
        close(fds[1]);
        if (execvp(file, argv) == -1)
            exit(1);
    }
    if (type == 'r') {
        close(fds[1]);
        dup2(out_backup, STDOUT_FILENO);
        return fds[0];
    } else {
        close(fds[0]);
        dup2(in_backup, STDIN_FILENO);
        return fds[1];
    }
    return -1;
}

int main() {
    int fd = ft_popen("ls", (char *const[]){"ls", NULL}, 'r');
    if (fd < 0) {
        printf("ERROR\n");
        return 1;
    }
    char buf[1080];
    read(fd, buf, 1080);
    printf("OUTPUT -> %s\n", buf);
    close(fd);

    printf("CAT OUTPUT:\n\n");
    int fd2 = ft_popen("cat", (char *const[]){"cat", NULL}, 'w');
    write(fd2, "Something long and uncommon\n", 28);
    close(fd2);
}