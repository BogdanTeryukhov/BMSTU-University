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

int KMPSubst(char *S, char *T){

    int *p = Prefix(S);

    int t = 0,i = 0;
    while (i < strlen(T)){
        while(t > 0 && S[t] != T[i])
            t = p[t-1];

        if(S[t] == T[i]) {
            t++;
        }
        if(t == 0) {
            free(p);
            return 0;
        }
        if(t == strlen(S)){
            t = p[t-1];
        }
        i++;
    }
    return 1;
}

int main(int argc, char **argv)
{
    char *S = argv[1], *T = argv[2];

    return KMPSubst(S,T) ? printf("yes\n") : printf("no\n");
}

