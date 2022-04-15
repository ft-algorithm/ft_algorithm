#include <stdlib.h>

double  check_mod(int size, int *nums)
{
    double  result;

    if (size % 2 == 0)
        result = ((double)nums[(size - 1) / 2] + (double)nums[size / 2]) / 2;
    else
        result = (double)nums[size / 2];
    return (result);
}

int *merge_arr(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
    int i;
    int j;
    int *nums3;
    
    i = 0;
    j = 0;
    nums3 = (int *)malloc(sizeof(int) * (nums1Size + nums2Size));
    if (!nums3)
        exit (0);
    while (i < nums1Size || j < nums2Size)
    {
        if (i < nums1Size && (j >= nums2Size || nums1[i] <= nums2[j]))
        {
            nums3[i + j] = nums1[i];
            i++;
        }
        else
        {
            nums3[i + j] = nums2[j];
            j++;
        }
    }
    return (nums3);
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    int     *nums3;
    double  result;

    nums3 = merge_arr(nums1, nums1Size, nums2, nums2Size);
    result = check_mod(nums1Size + nums2Size, nums3);
    free(nums3);
    return (result);
}
