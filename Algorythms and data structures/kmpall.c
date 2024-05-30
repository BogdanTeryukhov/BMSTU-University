#include <stdio.h>
#include <string.h>
#include <malloc.h>

int* Prefix(char *s)
{
    int *p = (int *)malloc(sizeof(int)*(strlen(s) + 1));
    int t = 0;
    p[0] = t;
    int i = 0;

    while (i < strlen(s)){
        while(t > 0 && s[t] != s[i])
            t = p[t-1];
        if(s[t] == s[i]) {
            t++;
        }
        p[i] = t;
        i++;
    }
    return p;
}

void KMPSubst(char *s, char *t){
    int *p = Prefix(s);
    int q=0, k=0;
    while(k < strlen(t)){
        while((q>0) && (s[q] != t[k])){
            q = p[q-1];
        }
        if (s[q] == t[k]) {
            q++;
        }
        if (q == strlen(s)){
            printf("%ul ",(k - strlen(s) + 1));
        }
        k++;
    }
    free(p);
}

void main(int argc, char **argv)
{
    KMPSubst(argv[1],argv[2]);
    return 0;
}