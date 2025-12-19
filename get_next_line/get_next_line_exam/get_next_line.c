#include "get_next_line.h"

int ft_stlen(char *s)
{
	int i;

	i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	return i;
}

void *ft_strchr(char *s, char c)
{
	int i;

	i = 0;
	while (*s != c)
	{
		s++;
		i++;
	}
	if (*s == c)
		return s + i;
	return NULL;
}

char *ft_strcpy(char *dst, char *src)
{
	char *start;

	start = dst;
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	return start;
}

void *ft_memmove(char *dst, char *src, int len)
{
	char *start;
	int i;

	start = dst;
	if (src < dst)
	{
		i = len;
		while (src[--i])
			dst[i] = src[i];
	}
	else
	{
		i = -1;
		while (++i < len)
			dst[i] = src[i];
	}
	return start;
}

int copy_buf_partial(char **ret, char *buf, int size2)
{
	char *temp;
	int size1;
	int j;

	size1 = ft_stlen(*ret);
	temp = malloc(size1 + size2 + 1);
	if (!temp)
		return 1;
	while (**ret)
		*temp++ = **ret++;
	j = 0;
	while (j < size2)
	{
		*temp++ = *buf++;
		j++;
	}
	*temp = 0;
	*ret = temp;
	return 0;
}

int copy_buf_full(char **ret, char *buf)
{
	return copy_buf_partial(ret, buf, ft_stlen(buf));
}

char *get_next_line(int fd)
{
	static char buf[BUFFER_SIZE] = "";
	char *ret = NULL;

	char *tmp = ft_strchr(buf, '\n');
	while (!tmp)
	{
		if (!copy_buf_full(&ret, buf))
			return NULL;
		int by_read = read(fd, buf, BUFFER_SIZE);
		if (by_read < 0)
			return NULL;
	}
	if (!copy_buf_partial(&ret, buf, tmp - buf + 1))
		return NULL;
	return ret;
}

int main()
{
	int fd = open("input.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Couldn't open\n");
		return 1;
	}
	printf("%s", get_next_line(fd));
}