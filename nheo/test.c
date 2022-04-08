#include <stdio.h>

int get_mid(int num)
{
    if (num % 2 == 0)
        return (num / 2);
    else
        return (num / 2 + 1);
}

double	get_result(int num1, int num2, int mod)
{
	if (mod)
		return (num1);
	else
		return ((double)(num1 + num2) / 2);
}

double	if_one_is_larger(int* nums1, int nums1Size, int* nums2, int nums2Size, int mid, int mod)
{
	if (nums1[0] > nums2[nums2Size - 1] && nums1Size >= nums2Size)
		return (get_result(nums1[mid - (nums2Size - 1)], nums1[mid - nums2Size], mod));
	if (nums2[0] > nums1[nums1Size - 1] && nums2Size >= nums1Size)
		return (get_result(nums2[mid - (nums1Size - 1)], nums2[mid - nums1Size], mod));
	if (nums1[0] > nums2[nums2Size - 1] && nums1Size < nums2Size)
		return (get_result(nums2[mid], nums2[mid - 1], mod));
	if (nums2[0] > nums1[nums1Size - 1] && nums2Size < nums1Size)
		return (get_result(nums1[mid], nums1[mid - 1], mod));
	return (0);
}

double	when_fir_or_last(int* nums1, int i, int* nums2, int j, int mod)
{
	if (i < 0)
		return (get_result(nums2[j - 1], nums1[0], mod));
	if (j < 0)
		return (get_result(nums1[i - 1], nums2[0], mod));
	return (0);
}

double	findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    int i;
    int j;
    int mid;
	int	mod;
    int temp;

	mod = (nums1Size + nums2Size) % 2;
    mid = get_mid(nums1Size + nums2Size);
    i = mid / 2;
    temp = i;
	if (nums1[0] > nums2[nums2Size - 1] || nums2[0] > nums1[nums1Size - 1])
		return (if_one_is_larger(nums1, nums1Size, nums2, nums2Size, mid, mod));
    while (1)
    {
        j = mid - i - 1;
        if (0 <= i && 0 <=  j && j < nums2Size && i < nums1Size)
        {
			if (i == 0 && nums1[i] <= nums2[j])
				return (get_result(nums1[i], nums2[j], mod));
			else if (j == 0 && nums2[j] <= nums1[i])
				return (get_result(nums2[j], nums1[i], mod));
            if (nums2[j - 1] <= nums1[i] && nums1[i] <= nums2[j])
                return (get_result(nums1[i], nums2[j], mod));
			else if (nums1[i - 1] <= nums2[j] && nums2[j] <= nums1[i])
                return (get_result(nums2[j], nums1[i], mod));
            else if (nums2[j - 1] > nums1[i])
                i += temp;
            else if (nums2[j - 1] <= nums1[i] && nums2[j] < nums1[i])
                i -= temp;
        }
        else
			return (when_fir_or_last(nums1, i, nums2, j, mod));
        temp /= 2;
    }
    return (1);
}

int	main(void)
{
	int	arr1[10] = {1,2};
	int	arr2[10] = {3,4};
	double result;
	
	result = findMedianSortedArrays(arr1, 2, arr2, 2);
	printf("%f", result);
	return (0);
}