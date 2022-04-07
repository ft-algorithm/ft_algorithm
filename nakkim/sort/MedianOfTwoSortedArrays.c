// nums[numsIndex]를 sum에 넣은 후 numsIndex 증가
void    putValueAndIncrease(int* sum, int sumIndex, int* nums, int* numsIndex)
{
    sum[sumIndex] = nums[*numsIndex];
    (*numsIndex)++;
}

int*    getHalf(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
    int*    sum;
    int     index1;
    int     index2;
    int     medium;
    
    index1 = 0;
    index2 = 0;
    medium = (nums1Size + nums2Size) / 2 + 1;  // 중간값 인덱스
    sum = (int*)malloc(sizeof(int) * medium);  // 두 배열 합칠 공간(중간값까지만 합침)
    while (index1 < nums1Size && index2 < nums2Size && (index1 + index2) < medium)
    {
        if (nums1[index1] < nums2[index2])  // 배열 비교해서 작은 값을 넣음
            putValueAndIncrease(sum, index1 + index2, nums1, &index1);
        else
            putValueAndIncrease(sum, index1 + index2, nums2, &index2);
    }
    if (index1 + index2 < medium)  // medium까지 채우기 전에 배열 하나를 다 넣은 경우
    {
        while (index1 < nums1Size && index1 + index2 < medium)
            putValueAndIncrease(sum, index1 + index2, nums1, &index1);
        while (index2 < nums2Size && index1 + index2 < medium)
            putValueAndIncrease(sum, index1 + index2, nums2, &index2);
    }
    return (sum);
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    
    double     result;
    int*        sum;
    int         medium;
    
    medium = (nums1Size + nums2Size) / 2 + 1;
    sum = getHalf(nums1, nums1Size, nums2, nums2Size);
    if ((nums1Size + nums2Size) % 2 == 1)  // 배열 사이즈가 홀수면 중간값 1개
        result =  sum[medium - 1];
    else  // 중간값 둘 더해서 2로 나누기
        result =  (sum[medium - 2] + sum[medium - 1]) / 2.0;
    free(sum);
    return (result);
}