#include <stdio.h>
#include <stdlib.h>

void Merge(int k, int l, int m, int *p){//из презентации (слияние)
    int t[m-k+1];
    int i = k;
    int j = l + 1;
    int h = 0;
    while(h < m - k + 1){
        if ((j <= m) && ((i == l + 1) || (abs(p[j]) < abs(p[i])))){
            t[h] = p[j];
            j++;
        }
        else{
            t[h] = p[i];
            i ++;
        }
        h++;
    }
    for (int r = 0; r < h; r++)
        p[r+k]=t[r];
}
void MergeSortRec(int low, int high, int *p){ //из презентации (рекурсивная функция слияния для сортированных подпоследовательностей)
    int med;
    if (low < high){
        med = (low + high) / 2;
        MergeSortRec(low, med, p);
        MergeSortRec(med+1, high, p);
        Merge(low, med, high, p);
    }
}
int main(){
    int n;
    scanf("%d", &n);
    int p[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &p[i]);
    }
    int *buffer = p;
    MergeSortRec(0, n-1, buffer);
    for(int i = 0; i < n; i++){
        printf("%d\n", p[i]);
    }
}
