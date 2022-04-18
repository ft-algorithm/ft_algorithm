#include <stdio.h>

#define MAX 194
#define FLAG 1024
void init(int *arr)
{
	int	idx;

	idx = 0;
	while (idx < MAX)
		arr[idx++] = 0;
	arr[77]  = 1000; // M
	arr[185] = 900 | FLAG;  // CM
	arr[68]  = 500;  // D
	arr[15]  = 400 | FLAG;  // CD
	arr[67]  = 100;  // C
	arr[168] = 90 | FLAG;   // XC
	arr[76]  = 50;   // L
	arr[144] = 40 | FLAG;   // XL
	arr[88]  = 10;   // X
	arr[97]  = 9 | FLAG;     // IX
	arr[86]  = 5;    // V
	arr[167] = 4 | FLAG;    // IV
	arr[73]  = 1;    // I
}

int romanToInt(char * s){
	int		total;
	int		arr[MAX];
	int		temp;
	short	*p;

	init(arr);
	total = 0;
	while(*s)
	{
		p = (short *)s;
        if (s[1] == '\0')
        {
		    temp = arr[*p % MAX];
            if (temp & FLAG)
            {
                total += temp & ~FLAG;
                s++;
            }
            else
                total += arr[*s % MAX];
        }
        else
            total += arr[*s % MAX];
		s++;
	}
	return (total);
}

int main()
{
	printf("%d", romanToInt("MCMXCIV"));
}
