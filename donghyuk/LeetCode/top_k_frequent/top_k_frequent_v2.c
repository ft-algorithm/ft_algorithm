/*
 * Author   : donghyuk
 * Date     : 2022.04.17
 * leetcode : https://leetcode.com/problems/top-k-frequent-elements
 * Purpose  : Given an integer array nums and an integer k, return the k most frequent elements.
 *
 * How to Solve?
 * - 아래 노션 참고
 * - https://graceful-atom-bb0.notion.site/Sort-d32392b7d2e64c799c4ae3317a06bfb1
 * */
#include <stdlib.h>
#include "sort.h"

typedef struct s_node
{
	int	val;
	int count;
}	t_node;

int list_cmp(const void* a, const void* b)
{
	return ((((t_node *)b)->count) - (((t_node *)a)->count));
}

/*
 * size보다 작은 수의 소수를 구한다.
 * 소수는 size에서 값을 1씩 빼면서 소수인지 아닌지 확인한다.
 * */
int getPrime(int size)
{
	int prime;
	int i;

	if (size < 2)
		return (1);
	prime = size;
	i = 2;
	while (i * i <= prime)
	{
		if (prime % i == 0)
		{
			i = 2;
			prime--;
			continue ;
		}
		break ;
	}
	return (prime);
}

/* 이중해싱을 통한 해시테이블 초기화
 * 1차 해싱
 *	사이즈 크기를 통한 나머지 연산을 통해 해시값(first_hash)을 구한다.
 * 충돌 시,
 *	2차 해싱을 통해 탐사 이동폭(step)을 구한다.
 *		step = prime - (prev_hash mod prime) (prev_hash = 이전 해시값)
 *		hash = first_hash + (idx2 * step)
 *	2차 해싱 후 또 충돌이 일어날 시
 *		idx2를 1증가 후 다시 2차 해싱을 시도한다.
 *		다음 빈 공간을 찾을 때까지 계속 반복한다.
 * */
t_node	*init_table(int *nums, int size, int prime)
{
	t_node	*table;
	int		idx;
	int		idx2;
	int		hash;
	int		temp;

	table = (t_node *)calloc(size, sizeof(t_node));
	if (!table)
		return (table);
	idx = 0;
	while (idx < size)
	{
		// 1차 해싱
		hash = nums[idx] % size;
		hash = (hash > 0) ? hash : -hash;
		if (table[hash].count != 0 && table[hash].val != nums[idx])
		{
			// 충돌 시 2차 해싱
			temp = hash;
			hash = prime - (hash % prime);
			idx2 = 1;
			hash = (temp + (idx2 * hash)) % size;
			while (table[hash].count != 0 && table[hash].val != nums[idx])
			{
				idx2++;
				hash = prime - (hash % prime);
				hash = (temp + (idx2 * hash)) % size;
			}
		}
		table[hash].val = nums[idx++];
		table[hash].count++;
	}
	return (table);
}

// 정렬된 테이블에서 k번째만큼 배열을 반환
int	*get_frequent_elems(t_node *table, int k)
{
	int	*result;
	int	idx;

	result = (int *)malloc(sizeof(int) * k);
	if (!result)
		exit(1);
	idx = 0;
	while (idx < k)
	{
		result[idx] = table[idx].val;
		idx++;
	}
	return (result);
}

int	*topKFrequent(int* nums, int size, int k, int* returnSize)
{
	t_node	*table;
	int		*result;

	*returnSize = k;
	table = init_table(nums, size, getPrime(size));
	quick_sort(table, size, sizeof(t_node), list_cmp);
	result = get_frequent_elems(table, k);
	free(table);
	return (result);
}
