#include "get_next_line.h"

void ft_strcpy(char *dst, char *src)
{
    while (*src)
        *dst++ = *src++;
    *dst = '\0';
}

char *get_next_line(int fd)
{
    static char buf[BUFFER_SIZE + 1];
    int bytes_read;
    char *nl;
    char *temp;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    nl = NULL;
    temp = NULL;
    while (1)
    {
        if (!buf[0])
        {
            bytes_read = read(fd, buf, BUFFER_SIZE);
            if (bytes_read == 0)
                break;
            else if (bytes_read < 0)
            {
                free(nl);
                return NULL;
            }
            buf[bytes_read] = '\0';
        }
        nl = ft_strjoin(temp, buf);
        free(temp);
        temp = nl;
        if (!nl)
            return NULL;
        ft_strcpy(buf, &buf[custom_strlen(buf)]);
        if (has_nl(nl))
            break;
    }
    return nl;
}

int main()
{
    int fd = open("input.txt", O_RDONLY);
    if (fd == -1)
        return 0;
    char *res;
    while ((res = get_next_line(fd)) != NULL)
        printf("%s", res);
    // get_next_line(fd);
    // get_next_line(fd);
    // get_next_line(fd);
    // get_next_line(fd);
    // get_next_line(fd);
}
