#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIRST_CASE 'I'
#define SECOND_CASE 'P'
#define THIRD_CASE 'D'

struct Trie {
    struct Trie *arcs[26];
    long kw, ks;
} *root;

typedef struct Trie Trie;

Trie* TrieBuild(){  // функция построения 'юнита'
    Trie *trie = malloc(sizeof(Trie)); // освобождение памяти под созданный юнит
    trie->kw = trie->ks = 0; // определение значений
    int i = 0;
    while (i < 26){
        trie->arcs[i] = NULL; // заполнение 'неопределенностями'
        i++;
    }
    return trie;
}

long Find_in_Alphabet(char k){ // Функция нахождения нужного элемента
    char key[26] = "abcdefghijklmnopqrstuvwxyz"; //запись алфавита в массив
    for (int i = 0; i < 26; i++){
        if (k == key[i]){ //каждый индекс соответстует букве
            return i;
        }
    }
}

void INSERT(Trie *rt, char *k){ // Метод вставки
    Trie *trie;
    trie = rt;
    long i, len_k = strlen(k), find_k;

    for(i = 0; i < len_k; i++){
        find_k = Find_in_Alphabet(k[i]);
        if (trie->arcs[find_k] == NULL){ // если значение не определено, то обращаемся к конструктору последовательности
            trie->arcs[find_k] = TrieBuild();
        }
        trie = trie->arcs[find_k];
        trie->ks++;
    }

    if (trie->kw != 0){
        trie = rt;
        for(i = 0; i < len_k; i++){
            find_k = Find_in_Alphabet(k[i]);
            trie = trie->arcs[find_k];
            trie->ks--;
        }
    }
    else{
        trie->kw++;
    }
}

void PREFIX(Trie *rt, char *k){
    Trie *trie;
    trie = rt;
    long i, len_k = strlen(k), find_k;
    for(i = 0; i < len_k; i++) {
        find_k = Find_in_Alphabet(k[i]);
        if (trie->arcs[find_k] == NULL){
            printf("%d\n", 0);
            return;
        }
        trie = trie->arcs[find_k];
    }
    printf("%ld\n", trie->ks);
}

void DELETE(Trie *rt, char *k){ //Функция удаления
    Trie *trie;
    trie = rt;
    long len_k = strlen(k), find_k;
    long i = 0;
    while (i < len_k){
        find_k = Find_in_Alphabet(k[i]);
        trie = trie->arcs[find_k];
        trie->ks--;
        i++;
    }
    trie->kw--;
}

int main()
{
    root = TrieBuild();
    long n;
    scanf("%ld", &n);
    char a[10];
    char *k = (char*)malloc(sizeof(char) * 100002);
    for(long i = 0; i < n; i++) {
        scanf("%s %s", a, k);
        switch (a[0]) { // Запускаем метод switch для нахождения нужного нам кейса
            case FIRST_CASE:
                INSERT(root, k);
                continue;
            case SECOND_CASE:
                PREFIX(root, k);
                continue;
            case THIRD_CASE:
                DELETE(root, k);
                continue;
        }
    }
    free(k);
    return 0;
}