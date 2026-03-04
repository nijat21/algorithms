#include "get_next_line.h"

char *ft_strchr(char *s, int c)
{
    int i = 0;
    while (s[i] && s[i] != c)
        i++;
    if (s[i] && s[i] == c)
        return s + i;
    else
        return NULL;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    // while (--n > 0)
    //     ((char *)dest)[n - 1] = ((char *)src)[n - 1];
    size_t i;

    i = -1;
    while (++i < n)
        ((char *)dest)[i] = ((char *)src)[i];
    ((char *)dest)[i] = 0;
    return dest;
}

size_t ft_strlen(char *s)
{
    size_t res = 0;
    while (s && s[res])
        res++;
    return res;
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
    size_t size1 = ft_strlen(*s1);
    char *tmp = malloc(size2 + size1 + 1);
    if (!tmp)
        return 0;
    ft_memcpy(tmp, *s1, size1);
    ft_memcpy(tmp + size1, s2, size2);
    tmp[size1 + size2] = '\0';
    free(*s1);
    *s1 = tmp;
    return 1;
}

int str_append_str(char **s1, char *s2)
{
    return str_append_mem(s1, s2, ft_strlen(s2));
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
    if (dest < src)
        return ft_memcpy(dest, src, n);
    else if (dest == src)
        return dest;
    size_t i = n;
    while (i > 0)
    {
        i--;
        ((char *)dest)[i] = ((char *)src)[i];
    }
    return dest;
}

char *get_next_line(int fd)
{
    static char b[BUFFER_SIZE + 1] = "";
    char *ret = NULL;
    char *tmp = ft_strchr(b, '\n');
    while (!tmp)
    {
        if (!str_append_str(&ret, b))
        {
            free(ret);
            return (NULL);
        }
        int read_ret = read(fd, b, BUFFER_SIZE);
        if (read_ret == -1)
        {
            free(ret);
            return (NULL);
        }
        b[read_ret] = 0;
        if (read_ret == 0)
        {
            if (ret && ret[0])
                return ret;
            else
            {
                free(ret);
                return NULL;
            }
        }
        tmp = ft_strchr(b, '\n');
    }
    if (!str_append_mem(&ret, b, tmp - b + 1))
    {
        free(ret);
        return NULL;
    }
    tmp++;
    b[0] = 0;
    if (tmp && *tmp)
    {
        size_t len = ft_strlen(tmp);
        ft_memcpy(b, tmp, len);
        b[len] = 0;
    }
    return ret;
}

// int main(int ac, char **av)
// {
//     (void)ac;
//     int fd = open(av[1], O_RDONLY);
//     if (!fd)
//         perror("open");

//     // char *str;
//     // while ((str = get_next_line(fd)) != NULL)
//     //     printf("%s", str);
//     printf("%s", get_next_line(fd));
// }
