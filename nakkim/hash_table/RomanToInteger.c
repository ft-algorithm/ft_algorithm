// 끝에서부터 수행
// subtraction 함수에서 뺄셈인지 확인
// 해시테이블에 값 저장해서 바로 사용하도록 함

#define SIZE 31

int myStrlen(char* s)
{
    int len;
    
    len = 0;
    while (s[len])
        len++;
    return (len);
}

void subtraction(char*s, int* hash, int* index, int* result)
{
    int sub;
    int symbol;
    
    sub = 0;
    symbol = hash[s[*index] % SIZE];
    if (symbol == 10 || symbol == 5)  // V or X 앞에 I
        sub = 1;
    else if (symbol == 50 || symbol == 100)  // L or C 앞에 X
        sub = 10;
    else if (symbol == 500 || symbol == 1000)  // D or M 앞에 C
        sub = 100;
    while (sub && *index > 0 && hash[s[*index - 1] % SIZE] == sub)
    {
        *result -= sub;
        (*index)--;
    }
}

void setHash(int* hash)
{
    hash['I' % SIZE] = 1;
    hash['V' % SIZE] = 5;
    hash['X' % SIZE] = 10;
    hash['L' % SIZE] = 50;
    hash['C' % SIZE] = 100;
    hash['D' % SIZE] = 500;
    hash['M' % SIZE] = 1000;
}

int romanToInt(char * s){
    int     result;
    int     index;
    int     *hash;
    
    hash = (int*)malloc(sizeof(int) * SIZE);
    setHash(hash);
    
    result = 0;
    index = myStrlen(s);
    while (--index >= 0)
    {
        result += hash[s[index] % SIZE];
        subtraction(s, hash, &index, &result);
    }
    free(hash);
    return (result);
}