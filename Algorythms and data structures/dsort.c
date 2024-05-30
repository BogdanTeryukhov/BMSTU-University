#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    //DistributionSort
    char s[1000000]={0};
    gets(s);
    int count[27]={0};
    int k, i = 0;
    int n = strlen(s);
    while (i < n){
        k = s[i]-97;
        count[k] += 1;
        i++;
    }
    i = 0;
    while (i < 26){
        while (count[i] > 0){
            count[i]--;
            printf("%c", (i + 97));
        }
        i++;
    }
    printf("\n");

    return 0;
}