#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int vsp(int nel);
int prev_vsp(int fib);
void shellsort(unsigned long nel,
               int (*compare)(unsigned long i, unsigned long j),
               void (*swap)(unsigned long i, unsigned long j));
int *array;
int compare(unsigned long i, unsigned long j);
void swap(unsigned long i, unsigned long j);
int main()
{
    int i, n;
    scanf("%d", &n);

    array = (int*)malloc(n * sizeof(int));
    for (i = 0; i < n; i++) scanf("%d", array+i);

    shellsort(n, compare, swap);
    for (i = 0; i < n; i++) printf("%d ", array[i]);
    printf("\n");

    free(array);
    return 0;
}


int vsp(int nel)
{
    int a = 0, b = 1, sum = 0;

    while(a + b < nel)
    {
        sum = a + b;
        a = b;
        b = sum;
    }
    return sum;
}
int prev_vsp(int fib)
{
    if(fib == 1) return 0;

    double prev_fib = fib / ((1 + sqrt(5)) / 2.0);
    return (int)round(prev_fib);
}
void shellsort(unsigned long nel,
               int (*compare)(unsigned long i, unsigned long j),
               void (*swap)(unsigned long i, unsigned long j))
{
    int d = vsp(nel);
    while(d >= 1)
    {
        for(int i = d; i < nel; i++)
        {
            int loc = i;
            while(loc - d >= 0 && compare(loc - d, loc) > 0)
            {
                swap(loc, loc - d);
                loc -= d;
            }
        }
        d = prev_vsp(d);
    }
}
int compare(unsigned long i, unsigned long j)
{
    if (array[i] == array[j]) return 0;
    return array[i] < array[j] ? -1 : 1;
}
void swap(unsigned long i, unsigned long j)
{
    int t = array[i];
    array[i] = array[j];
    array[j] = t;
}