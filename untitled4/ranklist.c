#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct RankList {
    char *str;
    long k;
    long *span;
    struct RankList **next;
};
struct RankList * Succ(struct RankList * list){
    return list->next[0];
}

struct RankList ** Skip(struct RankList * l, long m, long k, struct RankList **p)
{
    struct RankList * x = l;
    int i = m - 1;
    while (i >= 0){
        while ((x->next[i] != NULL) && x->next[i]->k < k){
            x = x->next[i];
        }
        p[i] = x;
        i--;
    }
    return p;
}

char * look(struct RankList *list, long m, long k)
{
    struct RankList ** p = malloc(sizeof(struct RankList*)*m);
    Skip(list, m, k, p);
    struct RankList * x = Succ(p[0]);
    free(p);
    return x->str;
}

struct RankList * Insert(struct RankList * list, long m, long k, char* c)
{
    struct RankList ** p = malloc(sizeof(struct RankList*)*m);
    Skip(list, m, k, p);
    struct RankList *xx = malloc(sizeof(struct RankList));
    xx->next = malloc(sizeof(struct RankList *)*m);
    xx->span = malloc(sizeof(long)*m);
    xx->str = c;
    xx->k = k;

    long r = (long) rand()*2;
    long i = 0;
    while ((i < m) && (r%2==0))
    {
        xx->next[i] = p[i]->next[i];
        p[i]->next[i] = xx;
        if (i == 0)
        {
            xx->span[i] = 1;
            if (xx->next[i] == NULL) xx->span[i] = 0;
            p[i]->span[i] = 1;
            if (p[i]->next[i] == NULL) p[i]->span[i] = 0;
        }
        else
        {
            struct RankList * e = p[i];
            long count = 0;
            while (e != xx)
            {
                e = e->next[0];
                count++;
            }
            long cp = p[i]->span[i];
            p[i]->span[i] = count;
            xx->span[i] = cp-count+1;
            if (xx->next[i] == NULL) xx->span[i] = 0;
            if (p[i]->next[i] == NULL) p[i]->span[i] = 0;
        }
        i++;
        r /= 2;
    }
    for (long j = i; j < m; j++)
    {
        xx->next[j] = NULL;
        xx->span[j] = 0;
        if (p[j]->next[j] != NULL) p[j]->span[j]++;
    }
    free(p);
}

struct RankList * Delete(struct RankList * list, long m, long k)
{
    struct RankList ** p = malloc(sizeof(struct RankList*)*m);
    Skip(list, m, k, p);
    struct RankList *res = Succ(p[0]);
    long i = 0;
    while ((i < m) && (p[i]->next[i] == res))
    {
        p[i]->next[i] = res->next[i];
        if (p[i]->next[i] == NULL) {
            p[i]->span[i] = 0;
        }
        else {
            p[i]->span[i] = p[i]->span[i] + res->span[i] - 1;
        }
        i++;
    }
    for (long j = i; j < m; j++)
    {
        if (p[j]->next[j] != NULL) p[j]->span[j]--;
    }
    free(p);
    return res;
}
long rang(struct RankList * list, long m, long k)
{
    struct RankList* e = list;
    long counter = 0;
    for (long i = m-1; i>=0;i--)
    {
        loop:;
        if (e->next[i] != NULL)
        {
            if (e->next[i]->k <= k)
            {
                if (e->str == NULL)
                {
                    counter += e->span[i] - 1;
                }
                else
                {
                    counter += e->span[i];
                }
            }
            else if (e->k == k)
            {
                return counter;
            }
            else
            {
                continue;
            }
            e = e->next[i];
            goto loop;
        }
        else
        {
            if (e->k == k)
            {
                return counter;
            }
            else
            {
                continue;
            }
        }
    }
}

int main()
{
    long n;
    scanf("%ld\n", &n);
    struct RankList *first = malloc(sizeof(struct RankList));
    long m = (long) log2((double )n)+1;

    first->next = malloc(sizeof(struct RankList *)*m);
    first->span = malloc(sizeof(long)*m);
    first->str = NULL;
    first->k = -1000000000;

    for (long j = 0; j < m; j++)
    {
        first->next[j] = NULL;
        first->span[j] = 0;
    }
    for (long i = 0; i < n; i++)
    {
        char s[25];
        gets(s);
        if (s[0]=='I' && s[1]=='N' && s[2]=='S' && s[3]=='E' && s[4]=='R' && s[5]=='T')
        {

            char then[100] = " ";
            strtok(s, then);
            long k = strtol(strtok(NULL, then), NULL, 10);
            char *c = malloc(sizeof(char)*100);
            strcpy(c, strtok(NULL, then));
            Insert(first, m, k, c);
        }
        else if (s[0]=='L' && s[1]=='O' && s[2]=='O' && s[3]=='K' && s[4]=='U' && s[5]=='P')
        {
            char then[100] = " ";
            strtok(s, then);
            long k = strtol(strtok(NULL, then), NULL, 10);
            puts(look(first, m, k));
        }
        else if (s[0]=='D' && s[1]=='E' && s[2]=='L' && s[3]=='E' && s[4]=='T' && s[5]=='E')
        {
            char then[100] = " ";
            strtok(s, then);
            long k = strtol(strtok(NULL, then), NULL, 10);
            struct RankList *c = Delete(first, m, k);

            free(c->next);
            free(c->span);
            free(c->str);
            free(c);
        }
        else
        {
            char then[100] = " ";
            strtok(s, then);
            long k = strtol(strtok(NULL, then), NULL, 10);
            printf("%ld\n", rang(first, m, k));
        }
    }
    struct RankList *e = first;
    while (e != NULL)
    {
        struct RankList * c = e;
        e = e->next[0];
        free(c->span);
        free(c->next);
        free(c->str);
        free(c);
    }
    return 0;
}

