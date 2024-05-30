#include <stdio.h>
#include <stdlib.h>

struct PriorityQueue {
    struct Pq *heap;
    int cap;
    int count;
};

struct Pq {
    int v;
    int k;
};

void initPriorityQueue(struct PriorityQueue *q, int cap)//конструктор очереди с приоритетами
{
    q->heap = calloc(cap, sizeof(struct Pq));
    q->cap = cap;
    q->count = 0;
}


struct Pq Pop(struct PriorityQueue *q)
{
    struct Pq x;
    x = q->heap[0];
    q->heap[0].k = -2147483647;

    struct Pq *p = q->heap;
    int size = q->cap;
    int cap = 0;
    int i = 0;

    while (i < size / 2) {
        int left = i * 2 + 1;
        int right = left + 1;
        int k = left;
        if(right < size && p[right].k > p[left].k)
            k = right;
        if(p[i].k >= p[k].k) {
            break;
        }

        //SWAP
        struct Pq temp = p[i];
        p[i] = p[k];
        p[k] = temp;

        i = k;
        cap = i;
    }
    return x;
}

void Insert(struct PriorityQueue *q, struct Pq v)
{
    int i;
    i = q->count;
    if (i == q->cap){
        printf("Error");
    }
    q->heap[i] = v;
    while (i > 0 && q->heap[i].k > q->heap[(i-1) / 2].k) {

        //SWAP
        struct Pq tmp = q->heap[i];
        q->heap[i] = q->heap[(i-1) / 2];
        q->heap[(i-1) / 2] = tmp;
        i = (i-1) / 2;
    }
    q->count += 1;
}

int main()
{
    int n;
    scanf("%d", &n);

    int m = 0;
    int size = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &size);
        m += size;
    }

    struct PriorityQueue q;

    initPriorityQueue(&q, m);
    int i = 0;
    while (i < m){
        int v;
        scanf("%d", &v);
        struct Pq a;

        a.v = v;
        a.k = -v;

        Insert(&q, a);
        i++;
    }

    for (int i = 0; i < m; i++)
        printf("%d ", Pop(&q).v);
    free(q.heap);
    return 0;
}

