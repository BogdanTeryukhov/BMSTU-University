#include <stdio.h>
#include <stdlib.h>

#define ENQUEUE 'N'
#define DEQUEUE 'D'
#define MAXIMUM 'M'
#define EMPTY 'M'
#define ENQ_OR_EMP 'E'

struct DoubleStack {
    int *data;
    __attribute__((unused)) int *max;
    int cap;
    int top1;
    int top2;
};

typedef struct DoubleStack Stack;

int StackEmpty1(Stack* s){
    return s->top1 == 0 ? 1 : 0;
}

int StackEmpty_2(Stack* s){
    return s->top2 == (s->cap - 1) ? 1: 0;
}

void Push1 (Stack* s, int x)
{
    if (s->top2 < s->top1){
        printf("Error");
    }
    s->data[s->top1] = x;



    if (s->top1 == 0){
        s->max[s->top1]=x;
    }
    else{
        if (s->max[s->top1 - 1] < x)
            s->max[s->top1] = x;
        else{
            s->max[s->top1]=s->max[s->top1 - 1];
        }
    }

    s->top1++;
}

void Push2 (Stack* s, int x)
{
    if (s->top2 < s->top1){
        printf("Error");
    }
    s->data[s->top2] = x;

    if (s->top2 == (s->cap-1)){
        s->max[s->top2]=x;
    } else{
        if (s->max[s->top2 + 1] > x){
            s->max[s->top2] = s->max[s->top2 + 1];
        }
        else{
            s->max[s->top2] = x;
        }
    }

    s->top2--;
}

int Pop1 (Stack* s){
    if (StackEmpty1(s)){
        printf("Error");
    }

    s->top1--;
    return s->data[s->top1];
}

int Pop2 (Stack* s){
    if (StackEmpty_2(s)){
        printf("Error");
    }

    s->top2++;
    return s->data[s->top2];
}

int QueueEmpty(Stack* s){
    return StackEmpty1(s) && StackEmpty_2(s) ? 1 : 0;
}

void Enqueue(Stack* s, int x){
    Push1(s, x);
}

int Dequeue(Stack* s){
    if (StackEmpty_2(s)) {
        while (!StackEmpty1(s)) {
            Push2(s, Pop1(s));
        }
    }
    return Pop2(s);
}

int Maximum(Stack s){
    return (s.top1 != 0) && ((s.top2 == s.cap - 1) ||
    ((s.top2 != s.cap - 1) && (s.max[s.top1 - 1]> s.max[s.top2 + 1]))) ? s.max[s.top1-1] : s.max[s.top2+1];
}


int main() {
    int i,n,j;
    char Stack[5];
    int x;
    scanf("%d", &n);

    struct DoubleStack s;

    s.data=(int*)malloc(100001*sizeof(int));
    s.max=(int*)malloc(100001*sizeof(int));

    s.cap=100000;
    s.top1=0;
    s.top2=99999;

    for (i = 0; i < n; i++) {
        scanf("%s", Stack);

        if (Stack[0] == ENQ_OR_EMP){
            if (Stack[1] == ENQUEUE){
                scanf("%d", &x);
                Enqueue(&s, x);
            }else if (Stack[1] == EMPTY){
                j = QueueEmpty(&s);
                if (j == 1){
                    printf("true\n");
                }
                else{
                    printf("false\n");
                }
            }
        }else if (Stack[0] == DEQUEUE){
            x = Dequeue(&s);
            printf("%d\n", x);
        }

        if (Stack[0] == MAXIMUM){
            j = Maximum(s);

            printf("%d\n", j);
        }
    }

    free(s.data);
    free(s.max);
    return 0;
}