#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int gcd(int a, int b){// алгоритм Евклида
    int t;
    a = abs(a);
    b = abs(b);
    while (b > 0) {
        a %= b;
        t = a;
        a = b;
        b = t;
    }
    return a;
}

void ComputeLogarithms(int m, int size,int *lg)//заполненине таблицы логарифмов для всех возможных длин отрезков
{
    int j = 0;
    for(int i = 1; i <= m; i++)
        for(;j < (1 << i); j++)
            lg[j] = i - 1;
}


int SparseTable_Query(int **ST, int l, int r, int *lg){//запрос к разреженной таблице
    int j = lg[r - l + 1];
    return gcd(ST[l][j], ST[r - (1 << j) + 1][j]);
}

void SparseTable_Build(int *v, int n, int *lg,int ***pST)//из презы, вместо while -> for
{
    int m = lg[n] + 1;
    int **ST = (int**)malloc(sizeof(int *) * n);//новая матрица размером n на m
    for (int i = 0; i < n; i++)
        ST[i] = (int*)malloc(sizeof(int) * m);

    for(int i = 0; i < n; i++) ST[i][0] = v[i];

    for(int i = 1; i < m; i++)
        for(int j = 0; j <= n - (1 << i); j++)
            ST[j][i] = gcd(ST[j][i-1], ST[j + (1 << (i - 1))][i - 1]);
    *pST = ST;
}

int main(){
    int n;
    scanf("%i", &n);
    int nums[n];

    for(int i = 0; i < n; i++) scanf("%i", &nums[i]);

    int m = log2(n) + 1,
            lg_size = (1 << (m + 1)),
            lg[lg_size];

    ComputeLogarithms(m, lg_size, lg);
    int **ST;
    SparseTable_Build(nums, n, lg, &ST);
    int c;
    scanf("%i", &c);
    for(int i = 0; i < c; i++)
    {
        int l, r;
        scanf("%i %i", &l, &r);
        printf("%d\n", SparseTable_Query(ST, l, r, lg));
    }

    for (int i = 0; i < n; i++)
        free(ST[i]);
    free(ST);
    return 0;
}