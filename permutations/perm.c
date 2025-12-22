#include <unistd.h>

int ft_strlen(char *str)
{
  int i = 0;
  while (str[i])
    i++;
  return i;
}

void ft_swap(char *a, char *b)
{
  char temp = *a;
  *a = *b;
  *b = temp;
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

void permutate(char *str, int l, int len)
{
  int i = 0;

  if (l == len - 1)
  {
    write(1, str, len);
    write(1, "\n", 1);
  }
  else
  {
    i = l;
    while (i < len)
    {
      ft_swap(str + l, str + i);
      permutate(str, l + 1, len);
      ft_swap(str + l, str + i);
      i++;
    }
  }
}

int main(int ac, char **av)
{
  if (ac != 2)
    return 1;
  char *str = av[1];
  int len = ft_strlen(str);
  ft_sort(str);
  permutate(str, 0, len);
  write(1, "final ->", 8);
  write(1, str, len);
}
