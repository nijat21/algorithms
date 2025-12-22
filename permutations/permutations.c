#include <unistd.h>
#include <stdio.h>

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return i;
}

void ft_swap(char *o, char *t)
{
    char temp;

    temp = *o;
    *o = *t;
    *t = temp;
}

void ft_sort(char *str)
{
    int i = -1;
    int j = 0;
    while (str[++i])
    {
        j = i;
        while (str[++j])
        {
            if (str[j] < str[i])
                ft_swap(str + j, str + i);
        }
    }
}

void permute(char *str, int l, int r)
{
    int i = 0;

    if (l == r)
    {
        write(1, str, ft_strlen(str));
        write(1, "\n", 1);
    }
    else
    {
        i = l;
        while (i <= r)
        {
            ft_swap(str + l, str + i);
            permute(str, l + 1, r);
            ft_swap(str + l, str + i);
            i++;
        }
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 1;
    if (ft_strlen(av[1]) == 1)
        return 0;
    char *str = av[1];
    int len = ft_strlen(str);
    ft_sort(str);
    permute(str, 0, len - 1);

    printf("Final -> %s\n", str);
    return 0;
}