// 0 ~ 9 배열을 생성해서 앞에 와야할 수 부터 링크드 리스트로 정렬
// 9부터 0까지 pop해서 문자열 연결
typedef struct element
{
    int             val;
    int             digit;
    struct element* next;
} Element;

int getFirstNum(int num)
{
    while (num / 10 != 0)
        num /= 10;
    return (num % 10);
}

void setArr(Element* arr)
{
    for (int i = 0; i < 10; i++)
    {
        arr[i].val = i;
        arr[i].next = NULL;
    }
}

int getDigit(int num)
{
    int digit;
    
    digit = 1;
    while (num / 10 != 0)
    {
        digit++;
        num /= 10;
    }
    return (digit);
}

Element*    createElement(int num)
{
    Element* element;
    
    element = (Element*)malloc(sizeof(Element));
    element->val = num;
    element->next = NULL;
    element->digit = getDigit(num);
    return (element);
}

int isBigger(Element* comparison, Element* target, int first)
{
    // 두 수를 붙여서 큰지...
    int                 multiplier;
    int                 digit;
    unsigned long long  comp_target;
    unsigned long long  target_comp;
    
    // case1: comp + target
    multiplier = 10;
    digit = target->digit;
    while (--digit > 0)
        multiplier *= 10;
    comp_target = (unsigned long long)comparison->val * multiplier + target->val;
    // case2: target + comp
    digit = comparison->digit;
    multiplier = 10;
    while (--digit > 0)
        multiplier *= 10;
    target_comp = (unsigned long long)target->val * multiplier + comparison->val;
    return (target_comp > comp_target);
}

void push(Element* arr, int num)
{
    Element*    curr;
    Element*    newNode;
    int         first;
    
    newNode = createElement(num);
    first = getFirstNum(num);
    curr = &arr[first];
    while (curr->next != NULL && !isBigger(curr->next, newNode, first))
        curr = curr->next;
    if (curr->next == NULL)
    {
        curr->next = newNode;
        return ;
    }
    newNode->next = curr->next;
    curr->next = newNode;
}

int isEmpty(Element* arr)
{
    Element* curr;
    for (int i = 0; i < 10; i++)
        if (arr[i].next != NULL)
            return (0);
    return (1);
}

Element* pop(Element* arr)
{
    Element*    remove;
    
    for (int i = 9; i >=0; i--)
    {
        if (arr[i].next == NULL)
            continue ;
        remove = arr[i].next;
        arr[i].next = remove->next;
        return (remove);
    }
    return (0);
}

char* myItoa(int num, int digit)
{
    char* result;
    
    result = (char*)malloc(sizeof(char) * digit);
    while (digit-- > 0)
    {
        *(result + digit) = num % 10 + '0';
        num /= 10;
    }
    return (result);
}

char* myStrCat(char* dest, char* str, int dest_len, int str_len)
{
    char*   result;
    int     index;
    
    result = (char*)malloc(sizeof(char) * (dest_len + str_len + 1));
    result[dest_len + str_len] = '\0';
    while (str_len-- > 0)
        result[dest_len + str_len] = str[str_len];
    while (dest_len-- > 0)
        result[dest_len] = dest[dest_len];
    free(dest);
    free(str);
    return (result);
}

// 숫자를 합쳐서 한번에 문자열로 변환하려 했으나
// 값이 얼마나 커질지 몰라서 각각 문자열 변환 후 붙이는 식으로 구현
char* getLargestNum(Element* arr)
{
    char*       result;
    Element*    popped;
    int         length;
    
    length = 0;
    result = (char*)malloc(sizeof(char));
    while (!isEmpty(arr))
    {
        popped = pop(arr);
        result = myStrCat(result, myItoa(popped->val, popped->digit), length, popped->digit);
        length += popped->digit;
    }
    while (length > 0)
    {
        if (result[length - 1] != '0')
            break ;
        length--;
    }
    if (length == 0)
    {
        free(result);
        result = (char*)malloc(sizeof(char) * 2);
        *result = '0';
        *(result + 1) = '\0';
    }
    return (result);
}

char * largestNumber(int* nums, int numsSize){
    Element firstNums[10];
    
    setArr(firstNums);
    for (int i = 0; i < numsSize; i++)
        push(firstNums, nums[i]);
    return (getLargestNum(firstNums));
}