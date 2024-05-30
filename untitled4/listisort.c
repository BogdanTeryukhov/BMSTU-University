#include <stdio.h>
#include <malloc.h>

struct element {struct element *back, *near;int v;};

void listisort(struct element* elem , long number){ //функция сортировки списка вставками
    struct element* double_l = elem;
    for (long i = 1; i < number; i++){
        struct element* one_l = double_l;
        long lun = i - 1;
        int initial = (*one_l).near->v;
        while ((one_l->v > initial) && lun >= 0){ //поиск нужного места вставки
            (*one_l).near->v = (*one_l).v;
            lun--;
            one_l = (*one_l).back;
        }
        (*one_l).near->v = initial;
        double_l = (*double_l).near;
    }
}

int main()
{
    long number;
    scanf("%ld", &number);
    struct element *p;
    struct element *pf;
    for (long i = 0; i<number;i++)
    {
        struct element *c = malloc(sizeof(struct element));
        scanf("%d", &(*c).v);
        if (i<=0){
            pf = c;
        }
        else{
            (*p).near = c;
            (*c).back = p;
        }
        p = c;
    }
    (*pf).back = p;
    (*p).near = pf;
    listisort(pf, number);
    p = pf;
    for (long i = 0; i<number;i++)
    {
        printf("%d ", (*p).v);
        struct element* c;
        c=p;
        if (i < number-1) p = (*p).near;
        free(c);
    }
    return 0;
}
