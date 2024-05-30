#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void maxprod(float *max_arr, int num){
    size_t mid = 0, las = 0, start = 0;
    float maxsum = max_arr[0],sum = 0;
    for (int i = 0; i < num; ++i) {
        sum = sum+max_arr[i];
        if (sum > maxsum){
            maxsum = sum;
            mid = start;
            las = i;
        }
        if (sum<0){sum = 0;start = i;}
    }
    printf("%d %d\n", mid, las);
}

int main(){
    int num;
    scanf("%d", &num);
    float *a = (float*)malloc(sizeof(float)*num); //числитель
    float *b = (float*)malloc(sizeof(float)*num); //знаменатель
    float *max_arr = (float*)malloc(sizeof(float)*num); //макс сумма

    for (int i = 0; i<num; i++){scanf("%f" "/" "%f", &a[i], &b[i]);}
    for(int i = 0; i<num; i++){max_arr[i]=log(a[i]/b[i]);}

    maxprod(max_arr, num);
    free(max_arr);
    free(a);
    free(b);
    return 0;
}