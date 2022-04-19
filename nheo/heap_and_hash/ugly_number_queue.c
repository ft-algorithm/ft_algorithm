#include<stdlib.h>
#include<limits.h>

typedef struct s_queue
{
    long long		val;
	struct s_queue	*next;
} t_queue;

t_queue	*pop_queue(t_queue *queue)
{
    int 	top;
	t_queue	*temp;

    top = queue->val;
	temp = queue;
	if (queue->next)
	{
		queue = queue->next;
		free(temp);
		temp = 0;
	}
    if (top == queue->val)
        queue = pop_queue(queue);
    return (queue);
}

t_queue  *create_queue(int n)
{
    t_queue  *queue;

    queue = (t_queue *)calloc(sizeof(t_queue), 1);
    if (!queue)
        exit(0);
    queue->val = n;
    return (queue);
}

void    insert_queue(t_queue *queue)
{
    int         i;
	t_queue		*temp;
	t_queue		*new_queue;
    long long   new[3];

    i = -1;
    new[0] = queue->val * 2;
    new[1] = queue->val * 3;
    new[2] = queue->val * 5;
	temp = queue;
    while (++i < 3)
    {
		if (new[i] < INT_MAX)
		{
			new_queue = create_queue(new[i]);
			while (temp->next && new_queue->val > temp->next->val)
				temp = temp->next;
			if (!temp->next)
				temp->next = new_queue;
			else
			{
				new_queue->next = temp->next;
				temp->next = new_queue;
			}
		}
    }
}

void	free_queue(t_queue *queue)
{
	t_queue	*temp;

	while (queue)
	{
		temp = queue->next;
		free(queue);
		queue = temp;
	}
}

int nthUglyNumber(int n){
    int     top;
    t_queue  *queue;

    queue = create_queue(1);
    while (n > 1)
    {
        insert_queue(queue);
        queue = pop_queue(queue);
		n--;
    }
		top = queue->val;
    free_queue(queue);
    return (top);
}
