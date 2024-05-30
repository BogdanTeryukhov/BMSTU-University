#include <stdio.h>

unsigned long binsearch(unsigned long nel, int (*compare)(unsigned long i))
{
    unsigned long a = 0, b = nel - 1, c = (b + a) / 2;
    while (a <= b){
        int res = compare(c);

        if (res == -1) a = c + 1;
        else if(res == 1) b = c - 1;
        else
            return c;

        c = (b + a) / 2;
    }

    return nel;
}

int array[] = { 1, 6, 322, 45,56, 685, 2532, 85878 };
const int k = 45;

int compare(unsigned long i)
{
    if (array[i] == k) return 0;
    if (array[i]  < k) return -1;
    return 1;
}

int main()
{
    printf("%lu\n", binsearch(8, compare));
    return 0;
}

