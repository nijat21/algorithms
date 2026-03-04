#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

int ft_scanf(const char *, ...);

int main(void)
{
    int x;
    char str[100];
    char c;

    // int converted = ft_scanf("%d", &x);
    // printf("Converted: %d\n", converted);
    // printf("Number: %d\n", x);

    // int converted = ft_scanf("      %s ", str);
    // printf("Converted: %d\n", converted);
    // printf("String: %s\n", str);

    int converted = ft_scanf("%d %s %c", &x, str, &c);
    printf("Converted: %d\n", converted);
    printf("Número: %d, String: %s, Carácter: %c\n", x, str, c);

    return 0;
}
