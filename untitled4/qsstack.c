#include <stdio.h>
#include <stdlib.h>

struct Task{int low;int high;};
struct Stack{int capacity;int top;struct Task *data;};
void s_construct(struct Stack *s, int n);
void s_pull(struct Stack *s, struct Task x);
struct Task s_remove(struct Stack *s);
int s_empty(struct Stack s){return s.top == 0;}
int separation(int *a, int low, int high);
void quicksort(int *a, int n);
void main()
{
    int n;
    scanf("%d", &n);
    int nums[n];
    for(int i = 0; i < n; i++) scanf("%d", &nums[i]);
    quicksort(nums, n);
    for(int i = 0; i < n; i++) printf("%d ", nums[i]);
    printf("\n");
}
void quicksort(int *a, int n)
{
    struct Stack tasks;
    s_construct(&tasks, n);
    struct Task init_task;
    init_task.low = 0;
    init_task.high = n - 1;
    s_pull(&tasks, init_task);

    while(!s_empty(tasks))
    {
        struct Task task = s_remove(&tasks);
        int low = task.low,
                high = task.high;
        if(low < high)
        {
            struct Task new_task;
            int q = separation(a, low, high);
            new_task.low = q + 1;
            new_task.high = high;
            s_pull(&tasks, new_task);

            new_task.low = low;
            new_task.high = q - 1;
            s_pull(&tasks, new_task);
        }
    }
    free(tasks.data);
}
void s_construct(struct Stack *s, int n)
{
    s->data = (struct Task *)malloc(sizeof(struct Task) * n);
    s->capacity = n;
    s->top = 0;
}
struct Task s_remove(struct Stack *s)
{
    s->top--;
    return s->data[s->top];
}
int separation(int *a, int low, int high)
{
    int i = low, j = low;

    for(; j < high; j++)
    {
        if(a[j] < a[high])
        {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;

            i++;
        }
    }

    int temp = a[i];
    a[i] = a[high];
    a[high] = temp;

    return i;
}
void s_pull(struct Stack *s, struct Task x)
{
    s->data[s->top] = x;
    s->top++;
}