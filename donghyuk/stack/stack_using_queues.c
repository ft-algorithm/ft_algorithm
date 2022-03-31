#include <stdbool.h>
#include <stdlib.h>

#define QUEUE_SIZE 100

typedef struct s_queue{
    int front;     // Queue front 인덱스
    int rear;      // Queue rear 인덱스
    int max_size;  // Queue 최대 사이즈
    int vals[];    // zero-length Array
}   t_Queue;

typedef struct s_myStack{
    t_Queue *mainQ;
    t_Queue *subQ;
} t_MyStack;

t_Queue *QueueCreate(int size)
{
    t_Queue *q;

    q = (t_Queue*)malloc(sizeof(t_Queue) + (sizeof(int) * size));
    q->front = -1;
    q->rear = -1;
    q->max_size = size;
    return (q);
}

/* isQueueEmpty
 *
 * 초기 생성 시 또는 pop 처리 후
 * Queue에 아무것도 없을 시 -1이 저장이 된다.
 * * */
bool isQueueEmpty(t_Queue *q)
{
    return (q->front == -1);
}

void moveQueueData(t_Queue *dst, t_Queue *src, int size)
{
	int	idx;

    if (!isQueueEmpty(src))
    {
		idx = -1;
        while (idx++ <= src->rear)
            dst->vals[idx + size] = src->vals[idx];
        dst->front = 0;
        dst->rear = src->rear + size;
        src->front = -1;
        src->rear = -1;
    }
}

void enQueue(t_Queue *q, int val)
{
    if (isQueueEmpty(q))
        q->front = 0;
    q->rear++;
    q->vals[q->rear] = val;
}

int deQueue(t_Queue *q)
{
    int result;

    result = q->vals[q->front++];
    if(q->front == q->rear + 1)
    {
        q->front = -1;
        q->rear = -1;
    }
    return (result);
}

bool isQueueFull(t_Queue *q)
{
    return (q->max_size == q->rear);
}

t_MyStack* myStackCreate() {
    t_MyStack *stack;

    stack = (t_MyStack *)malloc(sizeof(t_MyStack));
    stack->mainQ = QueueCreate(QUEUE_SIZE);
    stack->subQ = QueueCreate(QUEUE_SIZE);
    return (stack);
}

void myStackPush(t_MyStack* stack, int val) {
    t_Queue *tempQ;
    int    max_size;

    if (isQueueFull(stack->mainQ))
    {
        max_size = stack->mainQ->max_size;
        tempQ = QueueCreate(max_size * 2);
        moveQueueData(tempQ, stack->mainQ, 0);
        free(stack->mainQ);
        free(stack->subQ);
        stack->mainQ = QueueCreate(max_size * 2);
        stack->subQ = tempQ;
        moveQueueData(stack->mainQ, stack->subQ, 1);
    }
    else
    {
        moveQueueData(stack->subQ, stack->mainQ, 0);
        enQueue(stack->mainQ, val);
        moveQueueData(stack->mainQ, stack->subQ, 1);
    }
}

int myStackPop(t_MyStack* stack) {
    return (deQueue(stack->mainQ));
}

int myStackTop(t_MyStack* stack) {
    t_Queue *mainQ;

    mainQ = stack->mainQ;
    return (mainQ->vals[mainQ->front]);
}

bool myStackEmpty(t_MyStack* stack) {
    return (stack->mainQ->front == -1);
}

void myStackFree(t_MyStack* stack) {
    free(stack->mainQ);
    free(stack->subQ);
    free(stack);
}
