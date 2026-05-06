#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void close_prev_fd(int *fd) {
    if (*fd != -1) {
        close(*fd);
        *fd = -1;
    }
}

int wait_all() {
    int status;
    pid_t pid;
    int error = 0;
    while (1) {
        pid = wait(&status);
        if (pid == -1) {
            if (errno == EINTR)
                continue;
            if (errno == ECHILD)
                break;
            return 1;
        }
        if ((WIFEXITED(status) && WEXITSTATUS(status)) || WIFSIGNALED(status))
            error = 1;
    }
    return error;
}

int picoshell(char **cmds[]) {
    int fds[2];
    int prev_fd = -1;
    bool has_next;
    pid_t pid;
    int i = -1;
    while (cmds[++i]) {
        has_next = cmds[i + 1] ? true : false;
        if (has_next) {
            if (pipe(fds) == -1)
                return (close_prev_fd(&prev_fd), 1);
        }
        pid = fork();
        if (pid == -1) {
            close_prev_fd(&prev_fd);
            close(fds[0]);
            close(fds[1]);
            return 1;
        }
        if (pid == 0) {
            if (prev_fd != -1) {
                if (dup2(prev_fd, STDIN_FILENO) == -1)
                    exit(1);
                close_prev_fd(&prev_fd);
            }
            if (has_next) {
                if (dup2(fds[1], STDOUT_FILENO) == -1)
                    exit(1);
                close(fds[0]);
                close(fds[1]);
            }
            execvp(cmds[i][0], cmds[i]);
            exit(1);
        }
        close_prev_fd(&prev_fd); // reverts prev_fd back to -1
        if (has_next) {
            close(fds[1]);
            prev_fd = fds[0];
        }
    }
    return wait_all();
}

// int main() {
//     char **cmds[] = {(char *[]){"ls", NULL}, (char *[]){"cat", NULL}, (char *[]){"cat", NULL},
//                      NULL};
//     printf("RES -> %d\n", picoshell(cmds));
//     char **cmds[] = {(char *[]){"ls", NULL}, (char *[]){"cat", NULL}, (char *[]){"none", NULL},
//                      NULL};
//     printf("RES -> %d\n", picoshell(cmds));
// }