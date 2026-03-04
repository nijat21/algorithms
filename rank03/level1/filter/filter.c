#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

size_t ft_strlen(char *str)
{
	size_t i = 0;

	while(str[i])
		i++;
	return i;
}

int ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	i = -1;
	while(++i < n)
	{
		if((unsigned char)s1[i] != (unsigned char)s2[i])
			return 1;
	}
	return 0;
}

char* filter(char *str)
{
	char buf[1000000];
	ssize_t bytes;
	size_t i; 
	size_t j; 
	size_t len; 

	i = -1;
	while(1)
	{
		bytes = read(STDIN_FILENO, &buf[++i], 1);
		if(bytes == -1)
			return NULL; 
		else if(bytes == 0)
			break;
	}
	buf[++i] = 0;
	len = ft_strlen(str);
	i = -1;
	while(buf[++i])
	{
		if(ft_strncmp(&buf[i], str, len) == 0)
		{
			j = -1;
			while(++j < len)
				write(STDOUT_FILENO, "*", 1);
			i += len - 1;
		}
		else 
			write(STDOUT_FILENO, &buf[i], 1);
	}
	
	return str;
}

int main(int ac, char **av)
{
	if(ac != 2 || !av[1][0])
		return 1;
	if(!filter(av[1]))
		return 1;
}
