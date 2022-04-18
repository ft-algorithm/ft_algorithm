/*
 * Author   : donghyuk
 * Date     : 2022.04.17
 * leetcode : https://leetcode.com/problems/ugly-number-ii/
 * Purpose  : Given an integer n, return the nth ugly number.
 *
 * How to Solve?
 * 0. 초기값 : num = 1, count = 1
 * 1. num을 1씩 증가시키며 ugly_number인지 확인한다.
 * 2. 만약 ugly_number이면 count를 증가시킨다.
 * 3. count와 nth의 값이 같으면 해당 num을 리턴한다.
 */

/*
 * n을 dividend로 나눌수 있을 때까지 나눈다.
 * */
int	div(int n, int dividend)
{
	while (n % dividend == 0)
		n /= dividend;
	return n;
}

/*
 * n이 ugly_number인지 체크한다.
 * n을 2,3,5로 더이상 나눌 수 없을 때까지 나눈다.
 * n이 2,3,5의 소인수로만 이루어진 경우 n값은 1이되며 1을 리턴한다.
 * n이 1이 아닐경우 0을 리턴한다.
 * */
int is_ugly(int n)
{
	n = div(n, 2);
	n = div(n, 3);
	n = div(n, 5);
	return ((n == 1) ? 1 : 0);
}

int nthUglyNumber(int n){
	int	num;
	int	count;

	num = 1;
	count = 1;

	while (count < n)
	{
		num++;
		if (is_ugly(num))
			count++;
	}
	return (num);
}
