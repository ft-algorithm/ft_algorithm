/**
 * 규칙성을 찾았는데 쓸데없이 할당하고 비교하고 하는 과정이 있었다.
 * 어차피 ugly 배열의 최대 크기가 1690 -> 4(int) * 2000 = 8000 = 0.0008MB..
 * 스택 영역으로도 충분했다..
 * 그리고 왜 삼항 연산자를 쓸 생각을 못했을까..
 * 맨 아래 주석처리된 코드가 처음 제출했던 건데 엄청난 if문들에 한숨이 나온다.
 */

#define INDEX2 0
#define INDEX3 2
#define INDEX5 4
#define getMin(a, b) (a < b ? a : b)

void init(int* mul, int* ugly, int* size)
{
    *size = 1;
    ugly[0] = 1;
    mul[INDEX2] = 0;  // 2랑 곱할 인덱스
    mul[INDEX3] = 0;  // 3이랑 곱할
    mul[INDEX5] = 0;  // 5랑..
}

int nthUglyNumber(int n){
    int mul[6];
    int ugly[n];
    int size;
    int min;
    
    init(mul, ugly, &size);
    while (size < n)
    {
        mul[INDEX2 + 1] = ugly[mul[INDEX2]] * 2;
        mul[INDEX3 + 1] = ugly[mul[INDEX3]] * 3;
        mul[INDEX5 + 1] = ugly[mul[INDEX5]] * 5;
        min = getMin(getMin(mul[INDEX2 + 1], mul[INDEX3 + 1]), mul[INDEX5 + 1]);
        if (min == mul[INDEX2 + 1]) mul[INDEX2]++;
        if (min == mul[INDEX3 + 1]) mul[INDEX3]++;
        if (min == mul[INDEX5 + 1]) mul[INDEX5]++;
        ugly[size++] = min;
    }
    return (ugly[size - 1]);
}

/*
#define INDEX_2 0
#define INDEX_3 1
#define INDEX_5 2

typedef struct ugly
{
    int*    nums;
    int     capacity;
    int     used_size;
} Ugly;

int* createMuls(void)
{
    int*   muls;
    
    muls = (int*)malloc(sizeof(int) * 3);
    muls[INDEX_2] = 0;  // 2랑 곱할 거 인덱스
    muls[INDEX_3] = 0;  // 3이랑 곱할 거
    muls[INDEX_5] = 0;  // 5랑 곱할 거
    return (muls);
}

Ugly* createUgly(int capacity)
{
    Ugly*   ugly;
    
    ugly = (Ugly*)malloc(sizeof(Ugly));
    ugly->nums = (int*)malloc(sizeof(int) * (capacity));
    ugly->capacity = capacity;
    ugly->used_size = 1;
	ugly->nums[0] = 1;
    return (ugly);
}

void putUglyNum(Ugly* U, int* muls)
{
    if (2 * U->nums[muls[INDEX_2]] < 3 * U->nums[muls[INDEX_3]])
    {
        if (2 * U->nums[muls[INDEX_2]] < 5 * U->nums[muls[INDEX_5]])
        {
			// 현재 들어있는 마지막 수보다 클 경우에만 수 넣음
			// 같거나 작으면 패스
            if (2 * U->nums[muls[INDEX_2]] > U->nums[U->used_size - 1])
                U->nums[U->used_size++] = 2 * U->nums[muls[INDEX_2]];
            muls[INDEX_2]++;
        }
        else
        {
            if (5 * U->nums[muls[INDEX_5]] > U->nums[U->used_size - 1])
                U->nums[U->used_size++] = 5 * U->nums[muls[INDEX_5]];
            muls[INDEX_5]++;
        }
    }
    else
    {
        if (3 * U->nums[muls[INDEX_3]] < 5 * U->nums[muls[INDEX_5]])
        {
            if (3 * U->nums[muls[INDEX_3]] > U->nums[U->used_size - 1])
                U->nums[U->used_size++] = 3 * U->nums[muls[INDEX_3]];
            muls[INDEX_3]++;
        }
        else
        {
            if (5 * U->nums[muls[INDEX_5]] > U->nums[U->used_size - 1])
                U->nums[U->used_size++] = 5 * U->nums[muls[INDEX_5]];
            muls[INDEX_5]++;
        }
    }
}

void freeAll(Ugly* U, int* muls)
{
    free(muls);
    free(U->nums);
    free(U);
}

int nthUglyNumber(int n){
    int*    muls;
    Ugly*   U;
    int     nth;
    
    U = createUgly(n);
    muls = createMuls();
    while (U->used_size < n)
        putUglyNum(U, muls);
    nth = U->nums[n - 1];
    freeAll(U, muls);
    return (nth);
}
*/