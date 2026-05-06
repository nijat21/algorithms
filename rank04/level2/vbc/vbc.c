#include "vbc.h"

int *new_int(char c) {
    int *p = malloc(sizeof(int));
    if (!p)
        return NULL;
    *p = c - '0';
    return p;
}

static int *handle_sum(const char *str, int *pos);

static int *handle_bracket(const char *str, int *pos) {
    while (str[*pos] == '(') {
        (*pos)++;
        int *val = handle_sum(str, pos);
        if (!val)
            return NULL;
        (*pos)++;
        return val;
    }
    int *res = new_int(str[*pos]);
    (*pos)++;
    return res;
}

static int *handle_product(const char *str, int *pos) {
    int *left = handle_bracket(str, pos);
    if (!left)
        return NULL;
    while (str[*pos] == '*') {
        (*pos)++;
        int *right = handle_bracket(str, pos);
        if (!right) {
            free(left);
            return NULL;
        }
        *left *= *right;
        free(right);
    }
    return left;
}

static int *handle_sum(const char *str, int *pos) {
    int *left = handle_product(str, pos);
    if (!left)
        return NULL;
    while (str[*pos] == '+') {
        (*pos)++;
        int *right = handle_product(str, pos);
        if (!right) {
            free(left);
            return NULL;
        }
        *left += *right;
        free(right);
    }
    return left;
}

bool calculate(char *str) {
    int pos = 0;
    int *res = handle_sum(str, &pos);
    if (!res)
        return false;
    printf("%d\n", *res);
    free(res);
    return true;
}