#include <stdio.h>
#include <unistd.h>

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

int is_balanced(char *str)
{
    int balance = 0;
    int i = -1;
    while (str[++i])
    {
        if (str[i] == '(')
            balance++;
        else if (str[i] == ')')
        {
            balance--;
            if (balance < 0)
                return 0;
        }
    }
    return (balance == 0);
}

void find_min_remove(char *str, int *min_rem, int pos, int curr_rem)
{
    if (curr_rem > *min_rem)
        return;
    if (is_balanced(str))
    {
        if (curr_rem < *min_rem)
            *min_rem = curr_rem;
        return;
    }
    int i = pos;
    while (str[i])
    {
        if (str[i] == '(' || str[i] == ')')
        {
            char saved = str[i];
            str[i] = ' ';
            find_min_remove(str, min_rem, i + 1, curr_rem + 1);
            str[i] = saved;
        }
        i++;
    }
}

void solve(char *str, int min_rem, int pos, int curr_rem)
{
    if (curr_rem > min_rem)
        return;
    if (is_balanced(str) && curr_rem == min_rem)
    {
        puts(str);
        return;
    }
    int i = pos;
    while (str[i])
    {
        if (str[i] == '(' || str[i] == ')')
        {
            char saved = str[i];
            str[i] = ' ';
            solve(str, min_rem, i + 1, curr_rem + 1);
            str[i] = saved;
        }
        i++;
    }
}

int main(int ac, char **av)
{
    if (ac != 2 || av[1][0] == 0)
        return 1;
    char *str = av[1];
    int i = -1;
    while (str[++i])
    {
        if (str[i] != '(' && str[i] != ')')
            return 1;
    }
    int min_rem = ft_strlen(str);

    find_min_remove(str, &min_rem, 0, 0);
    // printf("%d", min_rem);
    solve(str, min_rem, 0, 0);
}