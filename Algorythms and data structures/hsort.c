#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>

void* P(void* base, size_t width, size_t i) {
    return (char*)base + width * i;
}

void swap(void* base, size_t width, size_t a, size_t b) {
    uint8_t* first = P(base, width, a);
    uint8_t* second = P(base, width, b);
    for (size_t i = 0; i < width; ++i) {
        uint8_t temp = *first;
        *first = *second;
        *second = temp;
        first++;
        second++;
    }
}

void heapify(void* base, size_t width, size_t i, size_t n,
             int (*compare)(const void* a, const void* b)) {
    while (true) {
        size_t l = 2 * i + 1;
        size_t r = l + 1;
        size_t j = i;
        if (l < n && P(base, width, i)<P(base, width, l)) {
            i = l;
        }
        if (r < n && P(base, width, i)<P(base, width, r)) {
            i = r;
        }
        if (i == j) {
            break;
        }
        swap(base, width, i, j);
    }
}

void build_heap(void* base, size_t width, size_t n,
                int (*compare)(const void* a, const void* b)) {
    size_t i = n/2 - 1;
    while (i >= 0){
        heapify(base, width, i - 1, n, compare);
        i--;
    }
}

void hsort(void* base, size_t n, size_t width,
           int (*compare)(const void* a, const void* b)) {
    if (n < 2) {
        return;
    }
    int i = n - 1;
    build_heap(base, width, n, compare);
    while (i > 0){
        swap(base, width, 0, i);
        heapify(base, width, 0, i, compare);
        i--;
    }
}

typedef struct {
    char* str;
    unsigned long a_count;
} mystring_t;

unsigned long ACalculator(char* str) {
    unsigned long ans = 0;
    while (*str != '\0') {
        if (*str == 'a') {
            ans++;
        }
        str++;
    }
    return ans;
}

int compare_mystring(const void* a, const void* b) {
    unsigned long l = ((const mystring_t*)a)->a_count;
    unsigned long r = ((const mystring_t*)b)->a_count;
    if (l < r) {
        return -1;
    }
    if (l == r) {
        return 0;
    }
    return 1;
}

int main() {
    size_t n;
    scanf("%zu", &n);
    mystring_t* arr = calloc(n, sizeof(mystring_t));
    for (size_t i = 0; i < n; ++i) {
        scanf("%ms", &arr[i].str);
        arr[i].a_count = ACalculator(arr[i].str);
    }
    hsort(arr, n, sizeof(mystring_t), compare_mystring);
    for (size_t i = 0; i < n; ++i) {
        puts(arr[i].str);
        free(arr[i].str);
    }
    free(arr);
    return 0;
}