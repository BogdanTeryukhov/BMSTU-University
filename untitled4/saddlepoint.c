#include <stdio.h>
#include <stdlib.h>

int main(){
    int n = 0,m = 0,l = 0;

    scanf("%d", &n);
    scanf("%d", &m);

    int a[n][m];

    int * b = (int *)malloc(n * sizeof(int));
    int * c = (int *)malloc(m * sizeof(int));

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d", &a[i][j]);
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){

            int k = a[i][j];

            if (i == 0)
                c[j] = k;

            if (j == 0)
                b[i] = k;

            if (k > b[i])
                b[i] = k;  //по строкам минимум

            if (k < c[j])
                c[j] = k;  //по столбцам минимум

        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){

            if (b[i] == c[j])
                printf("%d %d\n", i, j);
            else l++; //сколько раз встретилось невыполнение условия
        }
    }

    if (l == n*m) printf("none");

    free(b);
    free(c);
    return 0;
}
