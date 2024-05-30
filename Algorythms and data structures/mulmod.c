#include <stdio.h>

int main(){
    unsigned long a,b,m,k = 0;

    scanf("%ld", &a);
    scanf("%ld", &b);
    scanf("%ld", &m);

    int i = 63;
    while (i>=0){
        if (( (a >> i) & 1) == 1){  //реализация формулы (1)
            k += b;
            k %= m;
        }
        if (i != 0){
            k *= 2;
            k %= m;
        }
        i--;
    }

    printf("%ld\n", k);
    return 0;
}