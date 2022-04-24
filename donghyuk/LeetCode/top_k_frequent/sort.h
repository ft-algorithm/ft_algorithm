#ifndef SORT_H
# define SORT_H
# include <stdlib.h>

void	quick_sort(void *base, size_t total_elems, size_t size, int (*cmp)(const void* left, const void* right));
void	heap_sort();
#endif
