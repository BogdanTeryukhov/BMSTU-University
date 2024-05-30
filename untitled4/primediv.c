#include <stdio.h>
#include <stdlib.h>
#define SOLUTION {init(); solution();}

long *a;
long size;


void insert_sort(long j, long n){

    long elem = 0;
    long loc = 0;

    for (long i = j + 1; i <= n;){
        elem = a[i];
        int local = i - 1;
        for(;(local >= j) && ((labs(a[local])) > (labs(elem)));){
            a[local + 1] = a[local];
            local--;
        }
        loc = local;
        a[loc+1]=elem;
        i++;
    }
}

void merge_sort(long n, long l, long m){

    long v[m - n + 1];
    long i = n;
    long j = l + 1;

    for (long h = 0; h < (m-n+1);){
        if ((j<=m)&&((i==l+1)||(labs(a[j])<labs(a[i])))){
            v[h] = a[j];
            j++;
        }
        else{
            v[h] = a[i];
            i++;
        }
        h++;
    }
    for (long p = n; p <= m; p++) {
        a[p] = v[p-n];
    }
}

void my_sort(long low,long high){

    long s = low;
    long b = high;

    if ((b - s) < 5)
        insert_sort(s, b);
    else {
        long med;
        med = (s+b) / 2;
        my_sort(s, med);
        my_sort(med+1, b);
        merge_sort(s, med, b);
    }
}

void init(){
    scanf("%ld", &size);
    a = malloc(size * sizeof(long));
    for(int i = 0; i < size; i++){
        scanf("%ld", &a[i]);
    }
}

void solution(){
    my_sort(0, size - 1);
    int i = 0;
    while(i < size){
        printf("%ld ", a[i]);
        i++;
    }
}
int main(){
    SOLUTION;
    return 0;
}
