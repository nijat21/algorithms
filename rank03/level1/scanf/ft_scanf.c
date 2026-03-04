#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>

int match_space(FILE *f)
{
	int curr;
	curr = fgetc(f);
	while (curr != EOF && isspace(curr))
		curr = fgetc(f);
	if (curr != EOF)
		ungetc(curr, f);
	if (ferror(f))
		return -1;
	return (0);
}

int match_char(FILE *f, char c)
{
	int curr;

	curr = fgetc(f);
	if (curr == c)
		return (1);
	if (curr != EOF)
		ungetc(curr, f);
	return 0;
}

int scan_char(FILE *f, va_list *ap)
{
	char *res;
	int curr;

	res = va_arg(*ap, char *);
	curr = fgetc(f);
	if (isspace(curr))
	{
		ungetc(curr, f);
		return 0;
	}
	*res = (char)curr;
	return (1);
}

int scan_int(FILE *f, va_list *ap)
{
	int *num;
	int curr;
	int sign = 1;
	long res = 0;
	int matched = 0;

	num = va_arg(*ap, int *);
	curr = fgetc(f);
	if (curr == '+' || curr == '-')
	{
		if (curr == '-')
			sign = -1;
		curr = fgetc(f);
	}
	while (curr != EOF && isdigit(curr))
	{
		res = res * 10 + (curr - '0');
		matched++;
		curr = fgetc(f);
	}
	if (curr != EOF)
		ungetc(curr, f);
	if (matched == 0)
		return 0;
	res *= sign;
	if (res > INT_MAX)
		res = INT_MAX;
	else if (res < INT_MIN)
		res = INT_MIN;
	*num = (int)res;
	return (1);
}

int scan_string(FILE *f, va_list *ap)
{
	char *res;
	int curr;
	int matched = 0;

	res = va_arg(*ap, char *);
	curr = fgetc(f);
	while (curr != EOF && !isspace(curr))
	{
		*res = (char)curr;
		res++;
		matched++;
		curr = fgetc(f);
	}
	if (curr != EOF)
		ungetc(curr, f);
	if (matched > 0)
	{
		*res = 0;
		return 1;
	}
	return (0);
}

int match_conv(FILE *f, const char **format, va_list *ap)
{
	switch (**format)
	{
	case 'c':
		return scan_char(f, ap);
	case 'd':
		match_space(f);
		return scan_int(f, ap);
	case 's':
		match_space(f);
		return scan_string(f, ap);
	case '\0':
		return -1;
	default:
		return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, &ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}

	if (ferror(f))
		return EOF;
	return nconv;
}

int ft_scanf(const char *format, ...)
{
	va_list ap;
	int ret;

	va_start(ap, format);
	ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}
