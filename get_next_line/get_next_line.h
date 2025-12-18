#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 5
#endif

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>

char *ft_strjoin(char *s1, char *s2);
int custom_strlen(char *s);
bool has_nl(char *s);

#endif