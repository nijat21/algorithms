#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void print_arr(int *arr, int len)
{
    int i = -1;
    while (++i < len)
    {
        if (i > 0)
            fprintf(stdout, " ");
        fprintf(stdout, "%d", arr[i]);
    }
    fprintf(stdout, "\n");
}

int is_safe(int *board, int col, int row)
{
    int curr_col = -1;
    while (++curr_col < col)
    {
        if (board[curr_col] == row)
            return 0;
        if (board[curr_col] - row == col - curr_col || board[curr_col] - row == curr_col - col)
            return 0;
    }
    return 1;
}

void solve(int *board, int n, int col)
{
    if (col == n)
    {
        print_arr(board, n);
        return;
    }
    int row = -1;
    while (++row < n)
    {
        if (is_safe(board, col, row))
        {
            board[col] = row;
            solve(board, n, col + 1);
        }
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 1;
    int n = atoi(av[1]);
    if (n < 4)
        return 1;
    int *board = malloc(sizeof(int) * n);
    solve(board, n, 0);
    free(board);
}