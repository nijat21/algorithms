#include "get_next_line.h"

char *ft_strchr(char *s, int c)
{
	int i = 0;
	while (s && s[i] && s[i] != c)
		i++;
	if (s && s[i] && s[i] == c)
		return s + i;
	else
		return NULL;
}

// changed
void *ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i = -1;
	while (++i < n && dest && src && ((char *)src)[i])
		((char *)dest)[i] = ((char *)src)[i];
	((char *)dest)[i] = 0;
	return dest;
}

size_t ft_strlen(char *s)
{
	size_t res = 0;
	while (s && *s)
	{
		s++;
		res++;
	}
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

// changed
void *ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest < src)
		return ft_memcpy(dest, src, n);
	else if (dest == src)
		return dest;
	size_t i = n;
	((char *)dest)[n] = 0;
	while (--i >= 0 && dest && src && ((char *)src)[i])
		((char *)dest)[i] = ((char *)src)[i];
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
			return (NULL);
		int read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
			return (NULL);
		b[read_ret] = 0;
		if (read_ret == 0)
		{
			// if (ret && !ret[0])
			//     return NULL;
			return ret;
		} // added
		tmp = ft_strchr(b, '\n'); // added
	}
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return NULL;
	}
	ft_memmove(b, tmp + 1, ft_strlen(tmp));
	return ret;
}

// int main()
// {
//     int fd = open("input.txt", O_RDONLY);
//     if (fd < 0)
//         return 1;

//     // get_next_line(fd);
//     // get_next_line(fd);
//     // get_next_line(fd);
//     // get_next_line(fd);

//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
// }
