// 앞에 세가지 수 중에 중간값을 피봇으로 사용하기 위함
int findMiddle(int* nums, int start)
{
    if (nums[start] < nums[start + 1])
    {
        if (nums[start] > nums[start + 2])
            return (start);
        else if (nums[start + 1] < nums[start + 2])
            return (start + 1);
        else
            return (start + 2);
    }
    else
    {
        if (nums[start] < nums[start + 2])
            return (start);
        else if (nums[start + 1] > nums[start + 2])
            return (start + 1);
        else
            return (start + 2);
    }
}

void swap(int* nums, int index1, int index2)
{
    int tmp;
    
    tmp = nums[index1];
    nums[index1] = nums[index2];
    nums[index2] = tmp;
}

// 퀵정렬을 이용했습니다
void quickSort(int* nums, int numsSize, int left, int right)
{
    int pivot;
    int L;
    int R;
    
    if (right - left < 2)
    {
        if (nums[right] > nums[left])
            swap(nums, right, left);
        return ;
    }
    L = left;
    R = right;
    pivot = findMiddle(nums, left);
    while (L < R)
    {
        while (L < right && nums[L] >= nums[pivot])
            L++;
        while (R > left && nums[R] < nums[pivot])
            R--;
        if (L < R)
        {
            if (L == pivot || R == pivot)  // 피봇이면 스왑 스킵
            {
                if (L == pivot)
                    L++;
                else
                    R--;
            }
            else
                swap(nums, L++, R--);
        }
    }
    swap(nums, R, pivot);
    
    if (left < R)
        quickSort(nums, numsSize, left, R - 1);
    if (R < right)
        quickSort(nums, numsSize, R, right);
}

int findKthLargest(int* nums, int numsSize, int k){
    quickSort(nums, numsSize, 0, numsSize - 1);
    return (nums[k - 1]);
}