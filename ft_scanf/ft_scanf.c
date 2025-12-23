#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int ch;

    while ((ch = fgetc(f)) != EOF && isspace(ch))
        ;
    if (ch != EOF)
        ungetc(ch, f);
    return 0;
}

int match_char(FILE *f, char c)
{
    int ch;

    ch = fgetc(f);
    if (ch == EOF)
        return -1;
    if (ch != (unsigned char)c)
    {
        ungetc(ch, f);
        return 0;
    }
    return (1);
}

int scan_char(FILE *f, va_list ap)
{
    int ch = fgetc(f);
    if (ch == EOF)
        return 0;
    char *c = va_arg(ap, char *);
    *c = ch;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
    // You may insert code here // "20" -> 20
    int ch;
    int sign = 1, val = 0, count = 0;

    ch = fgetc(f);
    if (ch == EOF)
        return 0;

    if (ch == '-' || ch == '+')
    {
        if (ch == '-')
            sign = -1;
        ch = fgetc(f);
    }

    while (ch != EOF && isdigit(ch))
    {
        val = val * 10 + (ch - '0');
        count++;
        ch = fgetc(f);
    }
    if (ch != EOF)
        ungetc(ch, f);
    if (count == 0)
        return 0;
    int *p = va_arg(ap, int *);
    *p = val * sign;
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
    int count = 0;
    int ch = fgetc(f);
    char *str = va_arg(ap, char *);
    if (ch == EOF)
        return 0;
    while (ch != EOF && !isspace(ch))
    {
        *str++ = ch;
        count++;
        ch = fgetc(f);
    }
    if (ch != EOF)
        ungetc(ch, f);
    *str = 0;
    if (!count)
        return 0;
    return (1);
}

int match_conv(FILE *f, const char **format, va_list ap)
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
    case EOF:
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
            if (match_conv(f, &format, ap) != 1)
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
    va_start(ap, format);
    int ret = ft_vfscanf(stdin, format, ap);
    // ...
    va_end(ap);
    return ret;
}

int main(void)
{
    int n;
    int x;
    char s[32];
    char c;

    n = ft_scanf("%d %d %s %c", &n, &x, s, &c);

    printf("%d %d [%s] [%c]\n", n, x, s, c);
    return 0;
}