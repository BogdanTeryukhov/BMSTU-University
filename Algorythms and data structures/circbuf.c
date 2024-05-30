#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIRST_CASE 0
#define SECOND_CASE 1
#define THIRD_CASE 2

struct circbuf {int* data; int capacity, count, car, cdr;};

void queue_constructor(struct circbuf* circle_buffer, int n) {
    (*circle_buffer).data = (int*)malloc(sizeof(int) * n); // освобождение памяти под данные
    (*circle_buffer).capacity = n;
    (*circle_buffer).count = (*circle_buffer).car = (*circle_buffer).cdr = 0;
}
int queue_empty(struct circbuf circle_buffer) { return circle_buffer.count == 0; } //проверка на пустоту, функция "EMPTY"
void before_queue(struct circbuf* circle_buffer, int a) { // функция для "ENQ"
    int i = (*circle_buffer).cdr;
    (*circle_buffer).data[i] = a;
    (*circle_buffer).cdr += 1;
    if ((*circle_buffer).cdr == (*circle_buffer).capacity) {
        (*circle_buffer).capacity = (*circle_buffer).capacity * 2;
        (*circle_buffer).data = (int*)realloc((*circle_buffer).data, sizeof(int) * (*circle_buffer).capacity); // освобождение памяти под данные
    }
    (*circle_buffer).count += 1;
}
int aft_queue(struct circbuf* circle_buffer) { // функция для "DEQ"
    int i = circle_buffer->car;
    int a = (*circle_buffer).data[i];
    (*circle_buffer).car += 1;
    if ((*circle_buffer).car == (*circle_buffer).capacity) {
        (*circle_buffer).car = 0;
    }
    (*circle_buffer).count -= 1;
    return a;
}
int moves = 3;char* m_c[] = { "ENQ", "EMPTY", "DEQ"};
int move_index(char* move_c) {
    int i = 0;
    while (i < moves){
        if (strcmp(move_c, m_c[i]) == 0) //считываем индекс и смотрим какой кейс нам нужен
            return i;
        i += 1;
    }
    return -1;
}
int main() {
    int num;
    scanf("%d", &num);
    struct circbuf circle_buffer;
    queue_constructor(&circle_buffer, 4);
    int i = 0;
    while (i < num) {
        int a;
        char move_c[6];
        scanf("%s", move_c);
        int index = move_index(move_c);
        switch (index) {
            case FIRST_CASE:
                scanf("%d", &a);
                before_queue(&circle_buffer, a);
                break;
            case SECOND_CASE:
                if (queue_empty(circle_buffer)) { printf("true\n"); }
                else printf("false\n");
                break;
            case THIRD_CASE:
                printf("%d\n", aft_queue(&circle_buffer));
                break;
        }
        i += 1;
    }
    free(circle_buffer.data); // очищение данных кольцевого буфера
}

