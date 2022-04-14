#include <stdlib.h>
#include <string.h>

void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	compare(const void *a, const void *b)
{
	char	str_a[10];
	char	str_b[10];
	char	temp_a[20];
	char	temp_b[20];

	sprintf(str_a, "%d", (*(int *)a));
	sprintf(str_b, "%d", (*(int *)b));
	strcat(strcpy(temp_a, str_a), str_b);
	strcat(strcpy(temp_b, str_b), str_a);
	return (strcmp(temp_b, temp_a));
}

char * array_to_string(int* nums, int size)
{
    char    *result;
    char    *temp;
    int     idx;
    int     len;

    result = (char *)malloc(1000);
    idx = 0;
    len = 0;
    while (idx < size)
       len += sprintf(result + len, "%d", nums[idx++]);
    result[len] = '\0';
    return (result);
}

void quickSort(int *arr, int size, int (*cmp)(const void* left, const void* right)) {
	int left;
	int	right;
	int pivot;

	if (size < 1)
		return ;
	left = 1;
	pivot = 0;
	right = size - 1;
	/* patition */
	while(left <= right)
	{
		// left : 피벗보다 작은 값의 인덱스를 구한다.
		while (left < size && cmp(&arr[left], &arr[pivot]) < 0)
			left++;
		// right : 피벗보다 큰 값의 인덱스를 구한다.
		while (right > 0 && cmp(&arr[pivot], &arr[right]) < 0)
			right--;
		// left와 right의 인덱스가 교차할 경우 반복을 멈춘다.
		if (left >= right)
			break ;
		// left와 right의 값을 바꾼다.
		swap(&arr[left++], &arr[right--]);
	}
	/*
	 * 반복문을 빠져나왔을 경우,
	 * 배열 상에서 right(3)의 왼쪽 인덱스들(1,2)은 모두 pivot보다 큰 값이 된다.
	 * 그래서 pivot(0)의 값과 right(3)의 값을 변경하여 piviot의 왼쪽은 큰 값, 오른쪽은 작은 값으로 정렬 후,
	 * right(3)를 기점으로 다시 분할 정복한다.
	 */
	swap(&arr[right], &arr[pivot]);
	quickSort(arr, right , cmp);
	quickSort(arr + right + 1, size - right - 1,cmp);
}
