#include <stdlib.h>

/*
#define SWAP(a, b) do { \
    int temp;	\

    temp = *a;  \
    *a = *b;     \
    *b = temp;  \
} while (0)
*/

void	swap(void *a, void *b, size_t size)
{
	char	tmp;

	while (size > 0)
	{
		tmp = (*(char *)a);
		*((char *)a++) = (*(char *)b);
		*((char *)b++) = tmp;
		size--;
	}
}

void quick_sort(void *base, size_t total_elems, size_t size, int (*cmp)(const void* left, const void* right))
{
	char	*p_base;
	char	*left;
	char	*right;
	char	*pivot;
	char	*lo;
	char	*hi;

	if (total_elems < 1)
		return ;
	p_base = (char *)base;
	lo = p_base;
	hi = &lo[size * (total_elems - 1)];
	left = p_base + size;
	right = hi;
	pivot = p_base;
	/* patition */
	while(left <= right)
	{
		while (left < hi && cmp(left, pivot) < 0)
			left += size;
		while (right > lo && cmp(pivot, right) < 0)
			right -= size;
		if (left >= right)
			break ;
		swap(left, right, size);
		left += size;
		right -= size;
	}
	swap(right, pivot, size);
	quick_sort(p_base, (right - p_base) / size, size, cmp);
	quick_sort(right + size, (hi - right) / size, size, cmp);
}
