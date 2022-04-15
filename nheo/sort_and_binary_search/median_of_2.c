#include <stdio.h>

/*
Given two sorted arrays nums1 and nums2 of size m and n respectively,
return the median of the two sorted arrays.
The overall run time complexity should be O(log (m+n)).
*/

/*
	방식 : 홀수인 경우 arr1의 i번째 인덱스, arr2의 j번째 인덱스를 가져가서 N번째가 될 수 있는지 체크
	arr1에서 2개, arr2에서 2개를 가져가서 확인해본다.
	1) arr1의 i번째 인덱스가 중앙값일 경우
		- arr2[j - 1] <= arr1[i] <= arr2[j]
	2) arr2의 j번째 인덱스가 중앙값일 경우
		- arr2[i - 1] <= arr2[j] <= arr1[i]
	*) 짝수인 경우
		- arr1[i]가 중앙값이면 arr[i - 1]과 arr2[j - 1] 비교해서 더 큰 값이 중앙값이 된다.

	a) arr1[0]이 중앙값이 아닌 경우
		- arr2[j] < arr1[0]
	b) arr2[0]이 중앙값이 아닌 경우
		- arr1[i] < arr2[0]
	-> 중앙값이 아닌 경우만 따로 빼주면 됨.

	c) i < 1 || j < 1인 경우
		- i < 1인 경우
			-> arr1[i - 1] <= arr2[j] <= arr1[i]를 비교해야 하는데 i가 0이면 곤란.
			-> arr1[j]가 중앙값인지 알기 위해서는 arr1[i]랑만 비교해보면 됨
		- j < 1인 경우
			-> 마찬가지
*/

/*
	mid = 짝수인 경우(mid == 10)
	mid / 2 = 5
	따라서 여섯번째 인덱스를 찾아야 함.
	arr1[2], arr2[2]을 비교해야 함.
	따라서 i = mid / 2

	mid = 홀수인 경우(mid == 7)
	mid / 2 = 3
	따라서 네번째 인덱스를 찾아야 함.
	arr1[1], arr2[1]을 비교해야 함.

	따라서 i = mid / 2
*/

int		get_bigger(int num1, int num2)
{
	if (num1 < num2)
		return (num2);
	return (num1);
}

double	get_median(int* nums1, int i, int* nums2, int j, int mod)
{
	if (mod == 1)
		return (nums1[i]);
	if (i == 0)
		return ((double)(nums1[i] + nums2[j]) / 2);
	return (((double)(nums1[i] + get_bigger(nums1[i - 1], nums2[j])) / 2));
}

double	get_median2(int num1, int num2, int num3, int num4, int mod)
{

}

double	one_is_larger(int* nums1, int nums1Size, int* nums2, int nums2Size, int mid)
{
	int		mod;

	mod = (nums1Size + nums2Size) % 2;
	if (mid < nums2Size && nums2[mid - 1] <= nums1[0] && nums1[0] <= nums2[mid])
		return (get_median(nums1, 0, nums1, mid - 1, mod));
	if (mid < nums2Size && nums2[mid] < nums1[0])
		return (get_median(nums2, mid, nums2, mid - 1, mod));
	if (mid == nums2Size && nums2[mid - 1] <= nums1[0])
		return (get_median(nums1, 0, nums2, mid - 1, mod));
/*
	arr1의 mid가 중앙값인 경우
	arr2의 0이 중앙값인 경우
*/
	if (mid < nums1Size && nums1[mid - 1] <= nums2[0] && nums2[0] <= nums1[mid])
		return (get_median(nums2, 0, nums1, mid - 1, mod));
	if (mid < nums1Size && nums1[mid] < nums2[0])
		return (get_median(nums1, mid, nums1, mid - 1, mod));
	if (mid == nums1Size && nums1[mid - 1] <= nums2[0])
		return (get_median(nums2, 0, nums1, mid - 1, mod));
	return (0);
}

int		update_index(int *num1, int i, int *num2, int j, int mid)
{
	if (num1[i] < num2[j])
		return (i + (i + 1) / 2);
	return (i - (i + 1) / 2);
}

double	search_median(int* nums1, int nums1Size, int* nums2, int nums2Size, int mod)
{
	int		i;
	int		j;
	int		mid;

	mid = (nums1Size + nums2Size) / 2;
	i = mid / 2;
	j = mid - i;
	if ((mid <= nums2Size && nums1[0] > nums2[mid - 1]) || (mid <= nums1Size && nums2[0] > nums1[mid - 1]))
		return (one_is_larger(nums1, nums1Size, nums2, nums2Size, mid));
	while (1)
	{
		j = mid - i;
		if (nums2[j - 1] <= nums1[i] && nums1[i] <= nums2[j])
			return (get_median(nums1, i, nums2, j - 1, mod));
		else if (nums1[i] <= nums2[j - 1] && nums2[j - 1] <= nums1[i + 1])
			return (get_median(nums2, j - 1, nums1, i, mod));
		else
			i = update_index(nums1, i, nums2, j, mid);
	}
    return (0);
}

/*
	길이가 2일때
		- 2짜리가 둘 다 중앙값이거나
		- 하나만 중앙값이거나
		- 둘 다 중앙값이 아니거나
	길이가 1일때
		- 1짜리가 중앙값이거나
		- 중앙값이 아니거나
*/

// 따로 처리 필요ㅠㅠ
double	size_under_2(int* nums1, int nums1Size, int* nums2, int nums2Size, int mod)
{
	return (0);
}

double	findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
	int		mod;
	double	result;

	mod = (nums1Size + nums2Size) % 2;
	if (nums1Size <= 2 || nums2Size <= 2)
		result = size_under_2(nums1, nums1Size, nums2, nums2Size, mod);
	else
	result = search_median(nums1, nums1Size, nums2, nums2Size, mod);
	return (result);
}

int	main(void)
{
	int	a[2] = {1,2};
	int	b[2] = {1,1};

	printf("%f", findMedianSortedArrays(a, 2, b, 2));
	return (0);
}
