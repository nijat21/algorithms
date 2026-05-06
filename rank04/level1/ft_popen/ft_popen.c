#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
    The version of ft_peopen manipulating fds in child process.
*/

int ft_popen(const char *file, char *const argv[], char type) {
    int fds[2];
    pid_t pid;

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
    if (pid == 0) {
        if (type == 'r') {
            if (dup2(fds[1], STDOUT_FILENO) == -1)
                exit(1);
        } else {
            if (dup2(fds[0], STDIN_FILENO) == -1)
                exit(1);
        }
        close(fds[0]);
        close(fds[1]);
        if (execvp(file, argv) == -1)
            exit(1);
    }
    if (type == 'r') {
        close(fds[1]);
        return fds[0];
    } else {
        close(fds[0]);
        return fds[1];
    }
    return -1;
}

// int main() {
//     int fd1 = ft_popen("ls", (char *const[]){"ls", NULL}, 'r');
//     char buf[1080];
//     read(fd1, buf, 1080);
//     printf("LS OUTPUT:\n\n%s\n", buf);
//     close(fd1);

//     printf("CAT OUTPUT:\n\n");
//     int fd2 = ft_popen("cat", (char *const[]){"cat", NULL}, 'w');
//     write(fd2, "Something long and uncommon\n", 28);
//     close(fd2);
// }