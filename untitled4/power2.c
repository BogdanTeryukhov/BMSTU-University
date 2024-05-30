#include <stdio.h>

int power2(int a);
int power2_counter_p(int *a, int n, int bo, int summ);
int power2_counter(int *a, int n);

int main()
{
    int n;scanf("%d", &n);
    int nums[n];
    for(int i = 0; i < n; i++) scanf("%d", &nums[i]);
    printf("%d\n", power2_counter(nums, n));
    return 0;
}

int power2(int a)
{return a <= 0 ? 0 : !(a & (a - 1));}
int power2_counter(int *a, int n)
{int c = 0;
    for(int i = 0; i < n; i++)
        c += power2_counter_p(a, n, i, 0);
    return c;
}
int power2_counter_p(int *a, int n, int bo, int summ)
{
    summ += a[bo];
    int c = power2(summ);
    for (int j = bo + 1; j < n; j++)
        c += power2_counter_p(a, n, j, summ);
    return c;
}
