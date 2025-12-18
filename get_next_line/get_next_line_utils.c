#include "get_next_line.h"

int custom_strlen(char *s)
{
    int i;

    i = 0;
    while (s[i] && s[i] != '\n')
        i++;
    if (s[i] == '\n')
        i++;
    return i;
}

// Joins until the '\n'
char *ft_strjoin(char *line, char *buf)
{
    char *str;
    char *start;

    if (!line && !buf)
        return (NULL);
    if (!line)
        line = "";
    if (!buf)
        buf = "";
    str = malloc(custom_strlen(line) + custom_strlen(buf) + 1);
    if (!str)
        return (NULL);
    start = str;
    while (*line)
        *str++ = *line++;
    while (*buf && *buf != '\n')
        *str++ = *buf++;
    if (*buf == '\n')
        *str = '\n';
    str++;
    *str = '\0';
    return (start);
}

bool has_nl(char *s)
{
    int i;

    i = -1;
    while (s[++i])
    {
        if (s[i] == '\n')
            return true;
    }
    return false;
}
