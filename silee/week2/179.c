#include <stdio.h>
#include <stdlib.h>

int n_of_num(int num)
{
    if (num == 0)
        return (1);

    int len  = 0;
    while (num > 0)
    {
        num = num / 10;
        len++;
    }
    return (len);
} //index가 아닌 값. 1부터 시작.

int sum_of_num(int first, int second)
{
    int fir_n = n_of_num(first);
    int sec_n = n_of_num(second); 

    int fs = first;
    int sf = second;

    while (sec_n-- > 0)
        fs = fs * 10;
    while (fir_n-- > 0)
        sf = sf * 10;
    
    if (fs + second > sf + first)
        return (1);
    else
        return (0);

}

char	*ft_itoa(int n)
{
	int     len;
	char    *p;

	len = n_of_num(n);
	p = calloc(len, sizeof(char));
	if (!p)
		return (0);
	while (len-- > 0)
	{
		p[len] = n % 10 + '0';
		n = n / 10;
	}
	return (p);
}

char *largestNumber(int* nums, int numsSize){
    int out = 0;
    int in;
    int tmp = 0;
    int i = 0;
    char    *result;

    while (out < numsSize)
    {
        in = 0;
        while (in < numsSize)
        {
            if (sum_of_num(nums[in],nums[in + 1]) == 0)
            {
                tmp = nums[in];
                nums[in] = nums[in + 1];
                nums[in + 1] = tmp;
            }
            in++;
        }
        out++;
    }

	return (result);
}

int main()
{
    int *nums;
    int num[] ={9,4,1,2,78,4,1,2};
    nums = num;
    largestNumber(nums,7);
}
//버블? 퀵?
//일단 버블로 구현.