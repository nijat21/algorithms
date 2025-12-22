#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>

int ft_strncmp(char *s1, const char *s2, int n)
{
  int i = 0;

  while (i < n && s1[i] == s2[i])
    i++;
  if (i == n)
    return 0;
  return 1;
}

int ft_strlen(char *s)
{
  int i;

  i = 0;
  while (s[i])
    i++;
  return i;
}

void *censor(char *f)
{
  int i;
  char buf[1000000];
  int by_read;

  i = -1;
  while (1)
  {
    by_read = read(0, &buf[++i], 1);
    if (by_read == 0)
      break;
    else if (by_read == -1)
      return NULL;
  }
  buf[i] = 0;

  i = 0;
  while (buf[i])
  {
    int len = ft_strlen(f);
    if (ft_strncmp(&buf[i], f, len) == 0)
    {
      int j = -1;
      while (++j < len)
        write(1, "*", 1);
      i += len;
    }
    else
    {
      write(1, &buf[i], 1);
      i++;
    }
  }
  return f;
}

int main(int ac, char **av)
{
  if (ac != 2)
    return 1;

  if (!censor(av[1]))
    return 1;
}
