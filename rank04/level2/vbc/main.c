#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

bool calculate(char *str);

void unexpected(char c) {
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of input\n");
}

bool valid_char(char *str) {
    int i = 0;
    if (!isdigit(str[i]) || str[i] != '+' || str[i] != '*' || str[i] != '(' || str[i] != ')')
        return false;
    if (isdigit(str[i]) && (str[i + 1] && isdigit(str[i + 1])))
        return (unexpected(str[i + 1]), false);
    if (!str[i + 1] && (str[i] == '+' || str[i] == '*'))
        return (unexpected(0), false);
    return true;
}

bool valid_input(char *str) {
    int i = -1;
    int brackets = 0;
    while (str[++i]) {
        if (!valid_char(&str[i]))
            return false;
        if (str[i] == '(')
            brackets++;
        else if (str[i] == ')')
            brackets--;
        if (brackets < 0)
            return (unexpected(')'), false);
    }
    if (brackets != 0) {
        if (brackets > 0)
            return (unexpected('('), false);
        else
            return (unexpected(')'), false);
    }
    return true;
}

int main(int ac, char **av) {
    if (ac != 2)
        return 1;
    if (!valid_input(av[1]))
        return 1;
    if (!calculate(av[1]))
        return 1;
    return 0;
}