/**
 * 2022.04.15
 * Given an integer array nums and an integer k,
 * return the k most frequent elements. You may return the answer in any order.
 * 
 * 1. nums에 들어있는 수를 해시 테이블의 인덱스로 사용해서 카운트값을 구한다.
 * 2. 해시 테이블에 있는 값들을 힙으로 옮긴다.
 * 3. 루트를 제거하면서 k 번째 수를 구한다.
 */
typedef struct node
{
    int val;
    int count;
} Node;

typedef struct heap
{
    Node*   counts;
    int     used_size;
} Heap;

// 해시 테이블 생성
Node*   getCounts(int* nums, int numsSize)
{
    Node*   numCounts;
    int     hash;
    
    numCounts = (Node*)calloc(numsSize, sizeof(Node));
    for (int i = 0; i < numsSize; i++)
    {
        hash = nums[i] % numsSize;
        if (hash < 0)  // nums[i]의 값이 음수일 경우 양수로 바꿈
            hash = -hash;
		// 해시값 충돌이 발생하면 하나 증가시킨다.
        while (numCounts[hash].val != nums[i] && numCounts[hash].count)
        {
            hash++;
            if (hash == numsSize)  // 인덱스가 배열 크기와 같아지면
                hash = 0;
        }
        numCounts[hash].val = nums[i];
        numCounts[hash].count++;
    }
    return (numCounts);
}

// 힙 삽입 연산
void insert(Heap* heap, Node info)
{
    int curr;
    int parent;
    int tmp;

    heap->counts[heap->used_size].val = info.val;
    heap->counts[heap->used_size].count = info.count;
    curr = heap->used_size++;
    parent = (curr - 1) / 2;
    while (curr > 0)
    {
        if (heap->counts[parent].count >= heap->counts[curr].count)
            break ;
        tmp = heap->counts[parent].count;
        heap->counts[parent].count = heap->counts[curr].count;
        heap->counts[curr].count = tmp;
        tmp = heap->counts[parent].val;
        heap->counts[parent].val = heap->counts[curr].val;
        heap->counts[curr].val = tmp;
        curr = parent;
        parent = (curr - 1) / 2;
    }
}

void swapInfo(Heap* heap, int index1, int index2)
{
    int tmp;
    
    tmp = heap->counts[index1].val;
    heap->counts[index1].val = heap->counts[index2].val;
    heap->counts[index2].val = tmp;
    tmp = heap->counts[index1].count;
    heap->counts[index1].count = heap->counts[index2].count;
    heap->counts[index2].count = tmp;
}

// 힙 루트 제거(가장 큰 카운트 값)
int getRoot(Heap* heap)
{
    int root;
    int curr;
    int left;
    int right;
    int selected;
    
    root = heap->counts[0].val;
    memset(&(heap->counts[0]), 0, sizeof(Node));
    swapInfo(heap, 0, --(heap->used_size));
    curr = 0;
    while (1)
    {
        left = curr * 2 + 1;
        right = left + 1;
        if (left >= heap->used_size)  // 자식이 없을 경우
            break ;
        if (right >= heap->used_size)  // 자식이 하나일 경우
            selected = left;
        else
        {
            if (heap->counts[left].count > heap->counts[right].count)
                selected = left;
            else
                selected = right;
        }
		// 자식의 카운트 값보다 크면 멈춤
        if (heap->counts[selected].count < heap->counts[curr].count)
            break ;
        swapInfo(heap, curr, selected);
        curr = selected;
    }
    return (root);
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize){
    Node*   numCounts;
    Heap*   heap;
    int*    top_k;
    
    *returnSize = k;
    numCounts = getCounts(nums, numsSize);
    heap = (Heap*)malloc(sizeof(Heap));
    heap->counts = (Node*)malloc(sizeof(Node) * numsSize);
    heap->used_size = 0;
    for (int i = 0; i < numsSize; i++)
        if (numCounts[i].count)
            insert(heap, numCounts[i]);
    top_k = (int*)malloc(sizeof(int) * k);
    for (int i = 0; i < k; i++)
        top_k[i] = getRoot(heap);
    free(numCounts);
    free(heap->counts);
    free(heap);
    return (top_k);
}