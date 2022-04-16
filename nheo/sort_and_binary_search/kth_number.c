void    swap(int *num1, int *num2)
{
    int temp;
    
    temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

void	make_heap(int *nums, int size)
{
	int	i;
	int	j;
	int	root;

	j = size - 1;
	while (j > 1)
	{
		i = j;
		root = (i - 1) / 2;
		if (nums[i] < nums[root])
			swap(&nums[i], &nums[root]);
		while (i > 0)
		{
			if (i + 1 < size && nums[i] > nums[i + 1])
				swap(&nums[i], &nums[i + 1]);
			if (nums[i] < nums[root])
				swap(&nums[i], &nums[root]);
			i = root;
			root = (i - 1) / 2;
		}
		j--;
	}
}

void	get_smaller(int *nums, int size)
{
	int	i;
	int	root;

	root = 0;
    while (1)
    {
        i = root * 2 + 1;
        if (i + 1 < size && nums[i] > nums[i + 1])
            i++;
        if (i < size && nums[root] > nums[i])
            swap(&nums[root], &nums[i]);
        root = i;
        if (i >= size - 1)
            break ;
    }
}

void    heap_sort(int *nums, int size)
{
	int	i;

	i = 0;
	make_heap(nums, size);
	while (i < size - 1)
	{
		if (nums[0] < nums[size - 1 - i])
			swap(&nums[0], &nums[size - 1 - i]);
		get_smaller(nums, size - 1 - i);
		i++;
	}
}

int findKthLargest(int* nums, int numsSize, int k){
    heap_sort(nums, numsSize);
    return (nums[k - 1]);
}
