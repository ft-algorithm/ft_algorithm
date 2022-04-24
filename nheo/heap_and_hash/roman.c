#include <stdlib.h>

/*
	- 아이디어 : 해쉬테이블 사용해서 들어오는대로 계산
	- 빼야될거 체크하는 함수(4, 9)에 해당하는지 확인
*/

// 알파벳이니까 26이면 될거라 생각
#define HASH 26

int *init_roman(void)
{
    int *rom;

    rom = (int *)malloc(sizeof(int) * 26);
    if (!rom)
        exit(0);
    rom['I' % HASH] = 1;
    rom['V' % HASH] = 5;
    rom['X' % HASH] = 10;
    rom['L' % HASH] = 50;
    rom['C' % HASH] = 100;
    rom['D' % HASH] = 500;
    rom['M' % HASH] = 1000;
    return (rom);
}

int check_minus(int * roman, char **s)
{
    int result;
    int i;

    result = 0;
    i = *(*s + 1);
    if (roman[**s % HASH] == 1 && (roman[i % HASH] == 5 || roman[i % HASH] == 10))
        result -= roman[**s % HASH];
    else if (roman[**s % HASH] == 10 && (roman[i % HASH] == 50 || roman[i % HASH] == 100))
        result -= roman[**s % HASH];
    else if (roman[**s % HASH] == 100 && (roman[i % HASH] == 500 || roman[i % HASH] == 1000))
        result -= roman[**s % HASH];
    else
        return (result);
    *s = *s + 1;
    return (result);
}

int romanToInt(char * s){
    int *roman;
    int result;

    result = 0;
    roman = init_roman();
    while (*s)
    {
        if ((roman[*s % HASH] == 1 || roman[*s % HASH] == 10 || roman[*s % HASH] == 100))
            result += check_minus(roman, &s);
        result += roman[*s % HASH];
        s++;
    }
    return (result);
}
