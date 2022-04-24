/*
 * Author   : donghyuk
 * Date     : 2022.04.17
 * leetcode : https://leetcode.com/problems/top-k-frequent-elements
 * Purpose  : Given an integer array nums and an integer k, return the k most frequent elements.
 *
 * How to Solve?
 * 0. 이 버전은 퀵정렬만을 사용하여 문제를 해결했다. (해시 테이블,큐,힙 문제인줄 모르고...)
 * 1. 배열의 값들을 카운트하여 저장한다.
 *    - 값들을 카운트 하기 전, 배열을 정렬한다. [1, 3, 4, 2, 4, 1, 2, 3, 4] -> [1, 1, 2, 2, 3, 3, 4, 4, 4]
 *    - 정렬된 배열을 0인덱스부터 순차적으로 카운팅하여 배열(t_node)에 저장한다.
 * 2. 저장한 배열(t_node)을 카운트 별로 정렬한다. (내림차순)
 * 3. 정렬된 배열(t_node)의 k번째만큼 저장하여 반환한다.
 */

#include "sort.h"

typedef struct s_node
{
	int	val;
	int	count;
}	t_node;

int num_cmp(const void* a, const void* b)
{
	return ((*(int *)a) - (*(int *)b));
}

int list_cmp(const void* a, const void* b)
{
	return ((((t_node *)b)->count) - (((t_node *)a)->count));
}

void	count_nums(t_node *list, int *nums, int size)
{
	int	idx;
	int	cur_idx;
	int	cur_num;

	idx = 0;
	cur_idx = 0;
	while (idx < size)
	{
		list[cur_idx].val = nums[idx];
		while (idx < size && list[cur_idx].val == nums[idx])
		{
			list[cur_idx].count++;
			idx++;
		}
		cur_idx++;
	}
}

int	*get_frequent_elems(t_node *list, int k)
{
	int	*result;
	int	idx;

	result = (int *)malloc(sizeof(int) * k);
	if (!result)
		exit(1);
	idx = 0;
	while (idx < k)
	{
		result[idx] = list[idx].val;
		idx++;
	}
	return (result);
}

int	*topKFrequent(int* nums, int size, int k, int* returnSize)
{
	t_node *list;
	int	*result;

    *returnSize = k;
	list = (t_node*)calloc(size ,sizeof(t_node));
	if (!list)
		exit(1);
	quick_sort(nums, size, sizeof(int), num_cmp);
	count_nums(list, nums, size);
	quick_sort(list, size, sizeof(t_node), list_cmp);
	result = get_frequent_elems(list, k);
	free(list);
	return (result);
}
