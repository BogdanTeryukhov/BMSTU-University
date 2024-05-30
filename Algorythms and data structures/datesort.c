#include <stdio.h>
#include <stdlib.h>

struct Date { int Day, Month, Year; };
void print_it(struct Date* f, int n, int ms);
int assoc(struct Date f, int i_key);
struct Date* RadixSort(int q, int ms, struct Date* f, int n);
struct Date* dsort(int i_key, int ms, struct Date* f, int n);

int main() {
    int n, yyyy, mm, dd;
    scanf("%d", &n);
    struct Date* f = (struct Date*)malloc(sizeof(struct Date) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &yyyy, &mm, &dd);
        f[i].Day = dd;
        f[i].Month = mm;
        f[i].Year = yyyy;
    }
    int q = 4, ms = 256;
    struct Date* D = RadixSort(q, ms, f, n);
    print_it(D, n, ms);
    free(D); free(f);
    return 0;
}

void print_it(struct Date* f, int n, int ms) {
    for (int i = 0; i < n; i++) {
        printf("%d ", f[i].Year);
        if (f[i].Month < 10) {
            printf("0%d ", f[i].Month);
        }
        else
            printf("%d ", f[i].Month);
        if (f[i].Day < 10) {
            printf("0%d ", f[i].Day);
        }
        else
            printf("%d", f[i].Day);
        printf("\n");
    }
}

int assoc(struct Date f, int i_key) { //разряды
    if (3 - i_key == 0) {
        return f.Day;
    }
    else if (3 - i_key == 1) {
        return f.Month;
    }
    else if (3 - i_key == 2) {
        return f.Year % 256;
    }
    else if (3 - i_key == 3) {
        return f.Year / 256;
    }
}

struct Date* dsort(int i_key, int ms, struct Date* f, int n) {
    int* counter = (int*)malloc(sizeof(int) * ms);
    for (int i = 0; i < ms; i++) {
        counter[i] = 0;
    }
    for (int j = 0; j < n; ++j) {
        size_t k = assoc(f[j], i_key);
        counter[k] = counter[k] + 1;
    }
    for (int i = 1; i < ms; ++i) {
        counter[i] = counter[i] + counter[i - 1];
    }
    struct Date* D = (struct Date*)malloc(sizeof(struct Date) * n);

    for (int j = n - 1; j >= 0; --j) {
        size_t k = assoc(f[j], i_key);
        size_t i = counter[k] - 1;
        counter[k] = i;
        D[i] = f[j];
    }
    free(f);
    free(counter);

    return D;
}
struct Date* RadixSort(int q, int ms, struct Date* f, int n) {
    struct Date* D = (struct Date*)malloc(sizeof(struct Date) * n);
    int i;
    for (i = 0; i < n; i++)
        *(D + i) = *(f + i);

    for (int i = q - 1; i >= 0; --i) {
        D = dsort(i, ms, D, n);
    }
    return D;
}
