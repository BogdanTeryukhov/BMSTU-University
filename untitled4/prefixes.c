#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_answer(char *s, int *p, char *sp){// вывод префиксов
    int i = 0;
    int q;
    loop:
    if (i < strlen(s)) {
        q = i + 1;
        strncpy(sp, s, q);
        if ((q % (q - p[i]) == 0) && (q != (q - p[i]))){
            printf("%d ", q);
            printf("%d\n",(q / (q - p[i])));
        }
        i++;
        goto loop;
    }
}

void Prefix(char *s, int *p) {
    int len = strlen(s);
    int t = 0;
    for(int i = 1; i < len; i++) {
        for (; (t > 0) && (s[i] != s[t]); t = p[t - 1]);
        t += s[i] == s[t] ? 1 : 0;
        p[i] = t;
    }
}

void main(int argc, char **argv) {
    int l = (int)strlen(argv[1]);
    int *p=(int*)malloc((l+1) * sizeof(int));
    char *sp = (char*)malloc((l+1) * sizeof(char));

    for (int i = 0; i < l; ++i) {
        p[i] = 0;
    }
    Prefix(argv[1], p);
    print_answer(argv[1], p, sp);
    free(p);
    free(sp);
    return 0;
}