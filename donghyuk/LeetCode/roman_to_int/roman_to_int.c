/*
 * Author   : donghyuk
 * Date     : 2022.04.17
 * leetcode : https://leetcode.com/problems/roman-to-integer/
 * Purpose  : Given a roman numeral, convert it to an integer.
 *
 * How to Solve?
 * 1.
 */

#define SIZE 194
#define FLAG 1024

void init(int *table)
{
	int	idx;

	idx = 0;
	while (idx < SIZE)
		table[idx++] = 0;
	table['M' % SIZE]  = 1000;          // M
	table['D' % SIZE]  = 500;           // D
	table['C' % SIZE]  = 100;           // C
	table['L' % SIZE]  = 50;            // L
	table['X' % SIZE]  = 10;            // X
	table['V' % SIZE]  = 5;             // V
	table['I' % SIZE]  = 1;             // I
    table[0x4D43 % SIZE] = 900 | FLAG;  // CM (0x4D43)
	table[0x4443 % SIZE] = 400 | FLAG;  // CD
	table[0x4358 % SIZE] = 90  | FLAG;  // XC
	table[0x4C58 % SIZE] = 40  | FLAG;  // XL
	table[0x5849 % SIZE] = 9   | FLAG;  // IX
	table[0x5649 % SIZE] = 4   | FLAG;  // IV
}

int romanToInt(char * s){
	int		table[SIZE];
	int		total;
	int		temp;

	init(table);
	total = 0;
	while(*s)
	{
        temp = table[((s[1] << 8) + s[0]) % SIZE];
        if (temp & FLAG)
        {
            total += temp & ~FLAG;
            s++;
        }
        else
            total += table[*s % SIZE];
		s++;
	}
	return (total);
}
