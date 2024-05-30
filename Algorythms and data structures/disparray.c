#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math.h"

struct Sparse_arrays{ // определяем структуру разреженных массивов
    struct Sparse_arrays *next;
    int k, v;
};

struct Sparse_arrays **b;
int size, operations;

int GetInBasket(struct Sparse_arrays *sparse, int key){ //отвечает за заполнение наших массивов
    if(sparse == NULL) return 0;
    if(sparse->k == key) return sparse->v;
    return GetInBasket(sparse->next, key);
}

int At(int key){
    int hashKey = key % size;
    return GetInBasket(b[hashKey], key);
}

void Assign(int key, int value){
    struct Sparse_arrays *tmp = (struct Sparse_arrays *) malloc(sizeof(struct Sparse_arrays));
    tmp->k = key;
    tmp->v = value;
    tmp->next = b[key % size];
    b[key % size] = tmp;
}

void ClearBasket(struct Sparse_arrays *b){ //отвечает за очищение нашей 'корзины' (массивов)
    if(b != NULL)
        ClearBasket(b->next);
    free(b);// очищение b осуществляется именно в ClearBusket
}

void clean_struct(){
    int count = 0;
    while(count < size){
        b[count] = NULL;
        count++;
    }
}

void init(){ //конструктор наших разреженных массивов
    scanf("%d", &operations);
    scanf("%d", &size);
    b = (struct Sparse_arrays **)malloc(size * sizeof(struct Sparse_arrays *)); //выделяем память под структуру
    clean_struct();
}

void read_cmd(){
    for (long i = 0; i < operations; i++) {
        char *cmd;
        cmd = malloc(7 * sizeof(char));
        int k;
        scanf("%s ", cmd);
        scanf("%d", &k);
        if(strcmp(cmd, "AT") == 0){
            printf("%d\n", At(k));
        }else if (strcmp(cmd, "ASSIGN") == 0) {
            int v;
            scanf("%d", &v);
            Assign(k, v);
        }
        free(cmd);
    }
}

int main() {
    init();
    read_cmd();
    ClearBasket(*b);
    return 0;

}

