#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	p =(char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (0);
    p[len] = '\0';
    while (len-- > 0)
	{
		p[len] = n % 10 + '0';
		n = n / 10;
	}
 	return (p);
}

char	*ft_strjoin(char *result, char *str)
{
	int		sum;
	char	*res;

    sum = strlen(str);
    if (result)
        sum += strlen(result);
    res = (char *)malloc(sizeof(char) * (sum + 1));
	if (res == 0)
		return (0);
	*res = '\0';
    if (result)
    	strcat(res, result);
	strcat(res, str);
    free ((void *)result);
	return (res);
}

char *array2str(int *num, int numSize)
{
    char    *str;
    char    *result;
    int     i = 0;

    result = 0;
    while (i < numSize)
    {
        str = ft_itoa(num[i]);
        result = ft_strjoin(result, str);
        free (str);
        i++;
    }
    return (result);
}

char *largestNumber(int *nums, int numsSize)
{
    int tmp = 0;
    int i = 0;
    char    *result;
    
    for (int out = 0; out < numsSize; out++)
    {
        for (int in = 0; in < numsSize - 1; in++)
        {
            if ( sum_of_num(nums[in], nums[in + 1]) == 0)
            {
                tmp = nums[in];
                nums[in] = nums[in + 1];
                nums[in + 1] = tmp;
            }
        }
    }
    result = array2str(nums, numsSize);
	return (result);
}

int main()
{
    int *nums;
    int num[] ={9, 4, 1, 2, 78, 4, 1, 2};
    nums = num;
    
    printf("%s",largestNumber(nums,8));
}