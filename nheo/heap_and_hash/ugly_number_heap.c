/*
    풀이 방법 - 힙구조를 만들어서 해결.
    값 넣고 -> 맨 위에값 제거하고 반복한다.
    맨 처음에는 1만 있음
    맨 위에거에 *2, *3, *5 넣은 다음 맨 위에거 빼기
    반복
*/

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct s_heap
{
    long long   *val;
    int         last;
} t_heap;

void    swap(long long *num1, long long *num2)
{
    long long	temp;
    
    temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

void    make_heap(t_heap *heap)
{
    int root;
	int	i;
    int c;

	i = heap->last;
    while (i > 1)
    {
		c = i;
		root = (c - 1) / 2;
		if (heap->val[c] < heap->val[root])
			swap(&heap->val[c], &heap->val[root]);
        while (c > 0)
        {
			root = (c - 1) / 2;
            if (c < heap->last - 1 && heap->val[c] > heap->val[c + 1])
                swap(&heap->val[c], &heap->val[c + 1]);
            if (c < heap->last && heap->val[c] < heap->val[root])
                swap(&heap->val[c], &heap->val[root]);
            c = root;
        }
        i--;
    }
}

void	update_heap(t_heap *heap)
{
	int	root;
	int	c;

	root = 0;
	while (1)
	{
		c = root * 2 + 1;
		if (c > heap->last)
			break ;
		if (c < heap->last - 1 && heap->val[c] > heap->val[c + 1])
			c++;
		if (heap->val[root] > heap->val[c])
			swap(&heap->val[root], &heap->val[c]);
		root = c;
	}
}

int     pop_heap(t_heap *heap)
{
    int top;

    top = heap->val[0];
    swap(&heap->val[0], &heap->val[heap->last]);
	heap->val[heap->last] = 0;
    heap->last--;
    update_heap(heap);
    if (top == heap->val[0])
        top = pop_heap(heap);
    return (top);
}

void    insert_heap(t_heap *heap)
{
    int         i;
	int			flag;
    long long   new[3];

    i = -1;
	flag = 0;
    new[0] = heap->val[0] * 2;
    new[1] = heap->val[0] * 3;
    new[2] = heap->val[0] * 5;
    while (++i < 3)
    {
		if (new[i] < INT_MAX)
		{
			flag = 1;
			heap->last++;
			heap->val[heap->last] = new[i];
		}
    }
    make_heap(heap);
}

t_heap  *heap_init(int n)
{
    t_heap  *heap;

    heap = (t_heap *)calloc(sizeof(t_heap), 1);
    if (!heap)
        exit(0);
    heap->val = (long long *)calloc(sizeof(long long), n * 3 + 1);
    if (!heap->val)
        exit(0);
    heap->val[0] = 1;
    return (heap);
}

int nthUglyNumber(int n){
    int     top;
    t_heap  *heap;

    heap = heap_init(n);
    while (n > 0)
    {
        insert_heap(heap);
        top = pop_heap(heap);
		n--;
    }
    free(heap->val);
    free(heap);
    return (top);
}
