#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONST 0
#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4
#define MAX 5
#define MIN 6
#define NEG 7
#define DUP 8
#define SWAP 9

struct Stack
{
    int cap;
    int top;
    int *data;
};

void InitStack(struct Stack *s, int n)
{
    s->data = (int *)malloc(sizeof(int) * n);
    s->cap = n;
    s->top = 0;
}

void Push(struct Stack *s, int x)
{
    if (s->top == s->cap){
        printf("Error");
    }
    s->data[s->top] = x;
    s->top++;
}

int Pop(struct Stack *s)
{
    if (s->top == 0){
        printf("Error");
    }
    s->top--;
    return s->data[s->top];
}

char *INDEXES[10] = {"CONST",
                   "ADD",
                   "SUB",
                   "MUL",
                   "DIV",
                   "MAX",
                   "MIN",
                   "NEG",
                   "DUP",
                   "SWAP"};

int whatIndex(char *indexes)
{
    for(int i = 0; i < sizeof(INDEXES); i++)
        if(strcmp(indexes, INDEXES[i]) == 0)
            return i;
    return -1;
}

int main()
{
    int n;
    scanf("%d", &n);
    struct Stack stack;
    InitStack(&stack, n);

    for(int i = 0; i < n; i++)
    {
        char indexes[6];
        scanf("%s", indexes);

        int x;
        int y;
        int z;

        int ind = whatIndex(indexes);

        switch(ind)
        {
            case CONST:
                scanf("%d", &z);
                Push(&stack, z);
                break;
            case ADD:
                x = Pop(&stack);
                y = Pop(&stack);
                Push(&stack, x + y);
                break;
            case SUB:
                x = Pop(&stack);
                y = Pop(&stack);
                Push(&stack, x - y);
                break;
            case MUL:
                x = Pop(&stack);
                y = Pop(&stack);
                Push(&stack, x * y);
                break;
            case DIV:
                x = Pop(&stack);
                y = Pop(&stack);
                Push(&stack, x / y);
                break;
            case MAX:
                x = Pop(&stack);
                y = Pop(&stack);
                if(x > y)
                    Push(&stack, x);
                else
                    Push(&stack, y);
                break;
            case MIN:
                x = Pop(&stack),
                        y = Pop(&stack);
                if(x < y)
                    Push(&stack, x);
                else
                    Push(&stack, y);
                break;
            case NEG:
                x = Pop(&stack);
                Push(&stack, -x);
                break;
            case DUP:
                x = Pop(&stack);
                Push(&stack, x);
                Push(&stack, x);
                break;
            case SWAP:
                x = Pop(&stack);
                y = Pop(&stack);
                Push(&stack, x);
                Push(&stack, y);
                break;
        }
    }
    printf("%i\n", Pop(&stack));
    free(stack.data);
}
