#include <stdlib.h>
#include <stdio.h>

//숫자 정보를 담을 구조체 선언
typedef struct s_num
{
	char	*str;
	int		value;
	int		len;
}	t_num;

// 구조체 스왑 함수
void	swap_str(t_num *a, t_num *b)
{
	t_num	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/* 
	핵심은 숫자 두개 합친것중에 누가 더 큰지 비교하는것
	abcde abc 두개 숫자가 있다고 했을 때
	abcdeab // abcabcde 비교하려면 abc / a와 abcd 비교, abc / ab와 abcde 비교, ..., abc/abcde와 abcabcde 비교하는식으로 해야 함
*/
int	check_larger(t_num num1, t_num num2)
{
	int	len;
	int	i;
	int	j;
	int	temp1;
	int	temp2;

	i = 0;
	j = 0;
	temp1 = 0;
	temp2 = 0;
	len = num1.len + num2.len;
	/*
		temp1에는 첫번째 숫자 + 두번째 숫자,
		temp2에는 두번째 숫자 + 첫번째 숫자값이 들어감
	*/
	while (len--)
	{
		if (num1.str[i])
			temp1 += num1.str[i++];
		else
		{
			i = 0;
			temp1 += num1.str[i++];
		}
		if (num2.str[j])
			temp2 += num2.str[j++];
		else
		{
			j = 0;
			temp2 += num2.str[j++];
		}
		if (temp1 != temp2)
			return (temp1 - temp2);
	}
	return (0);
}

int	partition(t_num *nums, int start, int end, int pivot)
{
	int	i;
	int	j;

	while (1)
	{
		i = start;
		j = end - 1;
		//key보다 작은값 찾기
		while (nums[i].str[0] >= nums[pivot].str[0] && i < end - 1)
		{
			if (nums[i].str[0] == nums[pivot].str[0] && nums[i].value != nums[pivot].value && check_larger(nums[pivot], nums[i]) > 0)
				break ;
			i++;
		}
		//key보다 큰값 찾기
		while (nums[j].str[0] <= nums[pivot].str[0] && j > start)
		{
			if (nums[j].str[0] == nums[pivot].str[0] && nums[j].value != nums[pivot].value && check_larger(nums[j], nums[pivot]) > 0)
				break ;
			j--;
		}
		//작은값이 왼쪽에 있는 경우
		if (i < j)
			swap_str(&nums[i], &nums[j]);
		else
			break ;
	}
	//key보다 큰값이랑 교환
	if (nums[pivot].str[0] <= nums[j].str[0] && nums[pivot].value != nums[j].value && check_larger(nums[j], nums[pivot]))
		swap_str(&nums[j], &nums[pivot]);
	return (j);
}

void	quick_sort(t_num *nums, int start, int end)
{
	int	i;
	int	j;
	int	key;

	if (start >= end)
		return ;
	key = partition(nums, start, end, start);
	quick_sort(nums, start, key);
	quick_sort(nums, key + 1, end);
}

int	get_len(int num)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		num /= 10;
		i++;
	}
	return (i);
}

// itoa 함수 사용해 숫자를 문자열로 전환
char	*ft_itoa(int num, int len)
{
	int		i;
	char	*result;

	i = 0;
	result = (char *)malloc(sizeof(char) * len + 1);
	if (!result)
		exit(0);
	result[len] = 0;
	while (len--)
	{
		result[len] = num % 10 + '0';
		num /= 10;
	}
	return (result);
}

void	init_num(t_num *num_str, int num)
{
	num_str->value = num;
	num_str->len = get_len(num);
	num_str->str = ft_itoa(num, num_str->len);
}

char	*get_result(t_num *num_str, int len, int numsSize)
{
	int		i;
	int		j;
	int		k;
	char	*result;

	result = (char *)malloc(sizeof(char) * len + 1);
	if (!result)
		exit(0);
	i = -1;
	j = -1;
	while (++i < numsSize)
	{
		k = -1;
		while (num_str[i].str[++k])
		{
			// result의 첫값이 0이면 0이 가장 큰 값이므로 더 넣으면 안된다.
			if (*result == '0')
				break ;
			result[++j] = num_str[i].str[k];
		}
		free(num_str[i].str);
	}
	free(num_str);
	result[++j] = 0;
	return (result);
}

char	*largestNumber(int *nums, int numsSize)
{
	int		i;
	int		j;
	int		k;
	int		total_len;
	t_num	*num_str;

	i = -1;
	j = -1;
	total_len = 0;
	num_str = (t_num *)malloc(sizeof(t_num) * numsSize);
	if (!num_str)
		exit(0);
	while (++i < numsSize)
	{
		init_num(&num_str[i], nums[i]);
		total_len += num_str[i].len;
	}
	quick_sort(num_str, 0, numsSize);
	return (get_result(num_str, total_len, numsSize));
}
