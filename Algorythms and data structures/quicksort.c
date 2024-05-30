#include <stdio.h>

void sel(int *a, int low, int high);
int separation(int *a, int low, int high);
void quick_res(int *a, int low, int high, int m);
void q_sort(int *a, int n, int m);
int main()
{
    int n, m;
    scanf("%i %i", &n, &m);
    int a[n];
    for(int i = 0; i < n; i++) scanf("%i", &a[i]);
    q_sort(a, n, m);
    for(int i = 0; i < n; i++) printf("%i ", a[i]);
    printf("\n");
    return 0;
}

void q_sort(int *a, int n, int m)
{
    quick_res(a, 0, n - 1, m);
}
int separation(int *a, int low, int high)
{
    int i = low, j = low;

    for(; j < high; j++)
    {
        if(a[j] < a[high])
        {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;

            i++;
        }
    }

    int temp = a[i];
    a[i] = a[high];
    a[high] = temp;

    return i;
}
void sel(int *a, int low, int high)
{
    for(int j = high; j > low; j--)
    {
        int max_idx = j;

        for(int i = j - 1; i >= low; i--)
            if(a[i] > a[max_idx]) max_idx = i;

        int temp = a[j];
        a[j] = a[max_idx];
        a[max_idx] = temp;
    }
}
void quick_res(int *a, int low, int high, int m)
{
    if(high - low + 1 < m) sel(a, low, high);
    else
    {
        while(low < high)
        {
            int q = separation(a, low, high);
            if(q - low < high - q)
            {
                quick_res(a, low, q - 1, m);
                low = q + 1;
            }
            else
            {
                quick_res(a, q + 1, high, m);
                high = q - 1;
            }
        }
    }
}