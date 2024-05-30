#include <stdio.h>
#include <string.h>
char *S, *T;

int result(){
    long l1 = strlen(S), l2 = strlen(T), d[l1][26], j, k;
    int i = 0;
    cycle: //определем метку
    if(i < l1)
    {
        for(j = 0; j < 26; j++)
        {
            for (k = i; k >= 0; k--) if (((int)S[k] - 97) == j) break;
            d[i][j] = i - k;
        }
        i++;
        goto cycle;
    }
    i = 0;
    int temp = 0;
    while(i < (l2 - l1 + 1))
    {
        k = 0;
        for(j = 0; j < l1; j++){
            temp = d[j][(int)T[i + j] - 97];
            if (temp > k){
                k = temp;
            }
        }
        if (k == 0)
        {
            printf("%li", i);
            return 0;
        }
        i += k;
    }
    printf("%li", l2);
    return 0;
}

void main(int argc, char *argv[])
{
    S = argv[1];
    T = argv[2];
    if(result() == 0){
        return 0;
    }
}