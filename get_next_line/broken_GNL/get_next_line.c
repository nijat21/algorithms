#include "get_next_line.h"

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s && *s)
	{
		s++;
		i++;
	}
	return i;
}

char *ft_strchr(char *s, char c)
{
	int i;

	i = 0;
	while (s && s[i] && s[i] != c)
		i++;
	if (s && s[i] && s[i] == c)
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
	int i;
	int j;

	size1 = ft_strlen(*ret);
	temp = malloc(size1 + size2 + 1);
	if (!temp)
	{
		free(*ret);
		return 1;
	}
	i = 0;
	while (ret && *ret && (*ret)[i])
	{
		temp[i] = (*ret)[i];
		i++;
	}
	j = 0;
	while (j < size2)
	{
		temp[i] = buf[j];
		j++;
		i++;
	}
	temp[i] = 0;
	*ret = temp;
	return 0;
}

int copy_buf_full(char **ret, char *buf)
{
	return copy_buf_partial(ret, buf, ft_strlen(buf));
}

char *get_next_line(int fd)
{
	static char buf[BUFFER_SIZE] = "";
	char *ret = NULL;
	char *tmp = ft_strchr(buf, '\n');
	while (!tmp)
	{
		if (copy_buf_full(&ret, buf))
			return NULL;
		int by_read = read(fd, buf, BUFFER_SIZE);
		if (by_read < 0)
			return NULL;
		buf[by_read] = 0;
		if (by_read == 0)
		{
			if (ret && !ret[0])
				return NULL;
			return ret;
		}
		tmp = ft_strchr(buf, '\n');
	}
	if (copy_buf_partial(&ret, buf, tmp - buf + 1))
		return NULL;
	ft_memmove(buf, tmp + 1, ft_strlen(tmp));
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

	char *line;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
}
