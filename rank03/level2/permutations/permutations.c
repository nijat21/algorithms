#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

void ft_swap(char *c1, char *c2)
{
    char temp;
    temp = *c1;
    *c1 = *c2;
    *c2 = temp;
}

void ft_sort(char *str)
{
    int i = -1;
    int j;
    while (str[++i])
    {
        j = i;
        while (str[++j])
        {
            if (str[i] > str[j])
                ft_swap(&str[i], &str[j]);
        }
    }
}

int ft_strchr(char *str, char c)
{
    int i = -1;
    while (str[++i])
    {
        if ((unsigned char)str[i] == (unsigned char)c)
            return 1;
    }
    return 0;
}

void permute(char *str, char *arr, int pos, int len)
{
    if (pos == len)
    {
        write(1, arr, ft_strlen(arr));
        write(1, "\n", 1);
        return;
    }
    int i = -1;
    while (str[++i])
    {
        if (!ft_strchr(arr, str[i]))
        {
            arr[pos] = str[i];
            permute(str, arr, pos + 1, len);
            arr[pos] = 0;
        }
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 1;
    char *str = av[1];
    int len = ft_strlen(str);
    if (len == 1)
    {
        write(1, str, 1);
        return 0;
    }
    ft_sort(str);
    char *arr = malloc(len + 1);
    permute(str, arr, 0, len);
    free(arr);
}