
#include <stdio.h>
#include <malloc.h>
#include <string.h>
int power2(int x)
{
    if (x == 0) return 1;
    while (x > 1)
    {
        if (x % 2 != 0) return 0;
        x /= 2;
    }
    return 1;
}
int gyper(char c[], int z, int num)
{
    int v = 0;
    v = 1 << (c[z] - 'a');
    return v;
}

int min(int a, int b)
{
    if (a > b) return b;
    else return a;
}

int query(int t[], int i)
{
    int v = 0;
    while (i >= 0)
    {
        v = v ^ t[i];
        i = (i & (i + 1)) - 1;
    }
    return v;
}
int treequery(int t[], int l, int r)
{
    int v;
    v = query(t, r) ^ query(t, l - 1);
    return v;
}
int build(char c[], int l, int r, int t[], int num)
{
    int sum, bound, m;
    sum = 0;
    bound = min(r, num);
    while (l < bound)
    {
        m = (l + r) / 2;
        sum = sum ^ build(c, l, m, t, num);
        l = m + 1;
    }
    if (r < num)
    {
        sum = sum ^ gyper(c, r, num);
        t[r] = sum;
    }
    return sum;
}
int update(int i, int delta, int num, int t[])
{
    while (i < num)
    {
        t[i] = t[i] ^ delta;
        i = (i | (i + 1));
    }
    return 0;
}
int main()
{
    char *c;
    int len, i;
    c = (char*)malloc(1000001 * sizeof(char));
    gets(c);
    len = strlen(c);
    char *c2;
    c2 = (char*)malloc(1000001 * sizeof(char));
    int num, commands, r, left, right, *t, change;
    t = (int*)malloc(len * sizeof(int));
    char command[4];
    scanf("%d", &commands);
    for (r = 2; r < len; r = r * 2);
    build(c, 0, r - 1, t, len);
    for (i = 0; i < commands; i++)
    {
        scanf("%s", &command);
        if (strcmp("HD", command) == 0)
        {
            scanf("%d %d", &left, &right);
            if (power2(treequery(t, left, right)) == 1)
                printf("YES\n");
            else printf("NO\n");
        }
        else
        {
            scanf("%d ", &left);
            gets(c2);
            right = strlen(c2);
            for (int r = left; r < left + right; r++)
            {
                change = (1 << (c[r] - 'a'));
                c[r] = c2[r - left];
                change ^= (1 << (c[r] - 'a'));
                update(r, change, len, t);
            }
        }
    }
    free(t);
    free(c);
    free(c2);
    return 0;
}