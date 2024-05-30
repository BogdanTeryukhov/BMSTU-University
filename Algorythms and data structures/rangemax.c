
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxx(int a, int b){return a > b ? a : b;}
int line(int *T, int l, int r, int i, int a, int b);
int t_quer(int *T, int n, int l, int r);
void reboot(int j, int v, int i, int a, int b, int *T);
void t_reboot(int j, int v, int n, int *T);
void make(int *v, int i, int a, int b, int *T);
void t_make(int *v, int n, int **pT);

int main()
{
    int n;
    scanf("%i", &n);
    int nums[n];
    for(int i = 0; i < n; i++) scanf("%i", &nums[i]);

    int *T;
    t_make(nums, n, &T);

    int m;
    scanf("%i", &m);
    for(int i = 0; i < m; i++)
    {
        char action[3];
        int l, r;
        scanf("%s %i %i", action, &l, &r);
        if(strcmp("MAX", action) == 0)
            printf("%i\n", t_quer(T, n, l, r));
        else
            t_reboot(l, r, n, T);

    }

    free(T);
    return 0;
}
void t_make(int *v, int n, int **pT)
{
    int *T = (int *)malloc(sizeof(int) * (4 * n));
    make(v, 0, 0, n - 1, T);
    *pT = T;
}
void make(int *v, int i, int a, int b, int *T)
{
    if(a == b)
        T[i] = v[a];
    else
    {
        int m = (a + b) / 2;
        make(v, 2*i + 1, a, m, T);
        make(v, 2*i + 2, m + 1, b, T);
        T[i] = maxx(T[2*i + 1], T[2*i + 2]);
    }
}
void t_reboot(int j, int v, int n, int *T)
{
    reboot(j, v, 0, 0, n - 1, T);
}

void reboot(int j, int v, int i, int a, int b, int *T)
{
    if(a == b) T[i] = v;
    else
    {
        int m = (a + b) / 2;
        if(j <= m)
            reboot(j, v, 2*i + 1, a, m, T);
        else
            reboot(j, v, 2*i + 2, m + 1, b, T);
        T[i] = maxx(T[2*i + 1], T[2*i + 2]);
    }
}
int t_quer(int *T, int n, int l, int r)
{
    return line(T, l, r, 0, 0, n - 1);
}
int line(int *T, int l, int r, int i, int a, int b)
{
    if(l == a && r == b)
        return T[i];
    else
    {
        int m = (a + b) / 2;
        if(r <= m)
            return line(T, l, r, 2*i + 1, a, m);
        else if(l > m)
            return line(T, l, r, 2*i + 2, m + 1, b);
        else
            return maxx(line(T, l, m, 2*i + 1, a, m), line(T, m + 1, r, 2*i + 2, m + 1, b));
    }
}