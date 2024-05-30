#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Trie
{
    int v, exist;
    struct Trie *parents, **f;
};

struct Trie *Descend(struct Trie *a, char *k, int *pos)
{
    struct Trie *b;
    int len = strlen(k), i;
    for(i = 0; i < len; i++)
    {
        b = a->f[(int)k[i] - 97];
        if (b == NULL) break;
        b->v++;
        a = b;
    }
    pos[0] = i;
    return a;
};

struct Trie *DescendLook(struct Trie *a, char *k, int *pos)
{
    struct Trie *b;
    int len = strlen(k), i;
    for(i = 0; i < len; i++)
    {
        b = a->f[(int)k[i] - 97];
        if (b == NULL) break;
        a = b;
    }
    pos[0] = i;
    return a;
};

void DeleteEND(struct Trie *x)
{
    for(int i = 0; i < 26; i++)
    {
        if (x->f[i] != NULL)
        {
            DeleteEND(x->f[i]);
            free(x->f[i]);
        }
    }
}

int Delete(struct Trie *t, char *k, int *pos)
{
    struct Trie *a, *b;
    a = DescendLook(t, k, pos);
    int i = pos[0], len = strlen(k);
    if ((i != len) || (a->exist == 0)) return 0;
    a->exist = 0;
    a->v--;
    for(b = a->parents; b->parents != t; b = b->parents) b->v--;
    b->v--;
    return 0;
}

int LookUp(struct Trie *t, char *k, int *pos)
{
    struct Trie *x;
    x = DescendLook(t, k, pos);
    int i = pos[0], len = strlen(k);
    if (i != len) return 0;
    return x->v;
}

int Insert(struct Trie *t, char *k, int *v)
{
    struct Trie *x, *minus;
    x = Descend(t, k, v);
    int i = v[0], len = strlen(k);
    if ((i == len) && (x->exist != NULL))
    {
        for(minus = x; minus->parents != t; minus = minus->parents) minus->v--;
        minus->v--;
        return 0;
    }
    for(; i < len; i++)
    {
        struct Trie *y = (struct Trie*)malloc(sizeof(struct Trie));
        y->f = (struct Trie**)malloc(26 * sizeof(struct Trie*));
        for(int r = 0; r < 26; r++)  y->f[r] = NULL;
        y->exist = 0;
        x->f[(int)k[i] - 97] = y;
        y->v = 1;
        y->parents = x;
        x = y;
    }
    x->exist = 1;
    return 0;
}

int main()
{
    int n, *k = (int*)malloc(sizeof(int)), i;
    char *str = (char*)malloc(100000*sizeof(char)), command[7];
    scanf("%d", &n);
    struct Trie *t = (struct Trie*)malloc(sizeof(struct Trie));
    t->f = (struct Trie**)malloc(26 * sizeof(struct Trie*));
    for(i = 0; i < 26; i++) t->f[i] = NULL;
    for(i = 0; i < n; i++)
    {
        scanf("%s ", &command[i]);
        gets(str);
        if (strcmp("INSERT", command) == 0) Insert(t, str, k);
        if (strcmp("PREFIX", command) == 0) printf("%d ", LookUp(t, str, k));
        if (strcmp("DELETE", command) == 0) Delete(t, str, k);
    }
    free(k);
    free(str);
    DeleteEND(t);
    free(t->f);
    free(t);
    return 0;
}

