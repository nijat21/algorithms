#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_subs(int *arr, int len)
{
    int i = -1;
    while (++i < len)
    {
        if (i != 0)
            printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
}

void substrings(int *nums, int *arr, int l, int nums_len, int target, int sum, int arr_len)
{
    int i = -1;
    if (sum == target)
    {
        print_subs(arr, arr_len);
        return;
    }
    i = l;
    while (i < nums_len)
    {
        arr[arr_len] = nums[i];
        sum += arr[arr_len];
        arr_len++;
        substrings(nums, arr, i + 1, nums_len, target, sum, arr_len);
        arr_len--;
        sum -= arr[arr_len];
        i++;
    }
}

int main(int ac, char **av)
{
    int nums[ac - 2];
    int arr[ac - 2];
    int target;
    int i;

    if (ac < 3)
        return 1;
    target = atoi(av[1]);
    i = 1;
    while (++i < ac)
        nums[i - 2] = atoi(av[i]);
    substrings(nums, arr, 0, ac - 2, target, 0, 0);
}