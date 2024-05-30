#include <stdio.h>

union Int {
    int x;
    unsigned char bytes[4];
};
void distributionSort(int base, int c, union Int *nums, int n);
void radixsort(int base, int c, union Int *nums, int n);

int main()
{
    int n;
    scanf("%i", &n);
    union Int nums[n];
    for(int i = 0; i < n; i++)
        scanf("%i", &nums[i].x);
    radixsort(256, 4, nums, n);
    for(int i = 0; i < n; i++)
        printf("%i ", nums[i].x);
    printf("\n");
    return 0;
}
void radixsort(int base, int c, union Int *nums, int n)
{
    for(int i = 0; i < c; i++)
        distributionSort(base, i, nums, n);
}

void distributionSort(int base, int c, union Int *nums, int n) //алгоритм из презентации
{
    int count[base];
    int i = 0;
    while (i < base) {
        count[i] = 0;
        i++;
    }
    i = 0;
    while (i < n){
        int key = nums[i].bytes[c];
        if(c == 3) key ^= 128 ;
        count[key]++;
        i++;
    }
    i = 1;
    while (i < base){
        count[i] += count[i - 1];
        i++;
    }
    union Int sorted_nums[n];
    i = n - 1;
    while (i >= 0){
        int key = nums[i].bytes[c];
        if(c == 3) key ^= 128 ;
        int j = --count[key];
        sorted_nums[j] = nums[i];
        i--;
    }
    i = 0;
    while (i < n){
        nums[i] = sorted_nums[i];
        i++;
    }
}