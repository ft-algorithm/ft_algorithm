#include <stdlib.h>
/*
		왜 안되는거야 왜ㅠㅠㅠㅠ
		테이블 구조체에 count 세서
		count별로 heap 구조 만들어서 푸는데 메인문 돌릴때는 잘되는데 실행시키면 안됩니다ㅠㅠ
 */

typedef struct s_table
{
    int count;
    int value;
} t_table;

void    swap(t_table *a, t_table *b)
{
    t_table temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

int init_table(t_table **list, int *nums, int size)
{
    int     i;
    int     j;
    int     total;

    i = -1;
    j = 0;
	total = 0;
    *list = (t_table *)calloc(sizeof(t_table), size);
    if (!*list)
        exit(0);
    while (++i < size)
    {
        j = nums[i] % size;
		if (nums[i] < 0)
			j = -nums[i] % size;
        while ((*list)[j].count != 0 && (*list)[j].value != nums[i])
		{
            j++;
			if (j == size)
				j = 0;
		}
        if (!(*list)[j].count)
            total++;
        (*list)[j].count++;
        (*list)[j].value = nums[i];
    }
    return (total);
}

t_table *make_list(t_table *list, int init_size, int size)
{
    int     i;
    int     j;
    t_table *tb;

    tb = (t_table *)calloc(sizeof(t_table), init_size);
    if (!tb)
        exit(0);
    i = -1;
    j = 0;
    while (++i < size)
    {
        if (list[i].count > 0)
		{
            tb[j] = list[i];
			j++;
		}
    }
    return (tb);
}

void    make_heap(t_table *list, int size)
{
    int i;
    int c;
    int root;

    i = size - 1;
    while (1 < i)
    {
        c = i;
		if (list[c].count < list[root].count)
			swap(&list[c], &list[root]);
        while (c > 0)
        {
            root = (c - 1) / 2;
            if (c < size - 1 && list[c].count > list[c + 1].count)
                swap(&list[c], &list[c + 1]);
            if (list[c].count < list[root].count)
                swap(&list[c], &list[root]);
            c = root;
        }
        i--;
    }
}

void    sort_heap(t_table *list, int size)
{
    int i;
    int c;
    int root;

    i = size - 1;
    while (0 < i)
    {
		if (list[i].count > list[0].count)
	        swap(&list[i], &list[0]);
        i--;
        root = 0;
        while (1)
        {
            c = root * 2 + 1;
            if (c <= i - 1 && list[c].count > list[c + 1].count)
                c++;
            if (c <= i && list[c].count > list[root].count)
                swap(&list[c], &list[root]);
            root = c;
			if (c >= i - 1)
				break;
        }
    }
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize){
    int     total;
    int     *result;
    t_table *temp;
    t_table *list;

    total = init_table(&list, nums, numsSize);
    temp = make_list(list, total, numsSize);
    make_heap(temp, total);
    sort_heap(temp, total);
	*returnSize = k;
    result = (int *)malloc(sizeof(int) * k);
    while (k--)
        result[k] = temp[k].value;
    free(list);
    free(temp);
    return (result);
}
