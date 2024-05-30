#include <stdio.h>

int main(){
    int arr1[8],arr2[8];
    //Заполнение массивов элементами
    for (int i = 0; i<8; i++) scanf("%d", &arr1[i]);
    for (int i = 0; i<8; i++) scanf("%d", &arr2[i]);

    int summ1,summ2;
    summ1 = arr1[0]+arr1[1]+arr1[2]+arr1[3]+arr1[4]+arr1[5]+arr1[6]+arr1[7];
    summ2 = arr2[0]+arr2[1]+arr2[2]+arr2[3]+arr2[4]+arr2[5]+arr2[6]+arr2[7];
    if (summ1 == summ2){
        printf("yes");
    } else
        printf("no");



    return 0;
}

