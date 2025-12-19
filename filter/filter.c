#include <unistd.h>
#include <stdlib.h>
#define BUFFER_SIZE 20

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return i;
}

int ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (i < n && s1[i] == s2[i])
		i++;
	if (i == n)
		return 1;
	return 0;
}

void *filter(char *str)
{
	static char buf[100000];
	int bytes_read;
	char c;
	int i;
	int len;

	bytes_read = read(0, &c, 1);
	if (bytes_read < 0)
		return NULL;
	i = -1;
	while (bytes_read > 0)
	{
		buf[++i] = c;
		bytes_read = read(0, &c, 1);
		if (bytes_read < 0)
			return NULL;
	}
	buf[i] = '\0';
	len = ft_strlen(str);
	i = 0;
	while (buf[i])
	{
		if (ft_strncmp(&buf[i], str, len))
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
	return buf;
}

int main(int ac, char **av)
{
	if (ac != 2)
		return 1;

	if (!filter(av[1]))
		return 1;
	return 0;
}
