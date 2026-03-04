#include <stdio.h>
#include <stdlib.h>

void print_arr(int *arr, int len)
{
    int i = -1;
    while (++i < len)
    {
        if (i > 0)
            printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
}

void powerset(int *nums, int len, int *arr, int arr_len, int pos, int target, int sum)
{
    if (sum == target)
    {
        print_arr(arr, arr_len);
        if (pos == len)
            return;
    }
    int i = pos;
    while (i < len)
    {
        arr[arr_len] = nums[i];
        sum += arr[arr_len];
        arr_len++;
        powerset(nums, len, arr, arr_len, i + 1, target, sum);
        arr_len--;
        sum -= arr[arr_len];
        i++;
    }
}

int main(int ac, char **av)
{
    if (ac < 3)
        return 1;
    int len = ac - 2;
    int nums[len];
    int arr[len];
    int i = 1;
    while (++i < ac)
        nums[i - 2] = atoi(av[i]);
    int target = atoi(av[1]);
    powerset(nums, len, arr, 0, 0, target, 0);
}