// Runtime: 135 ms, faster than 40.00% of C online submissions for Network Delay Time.
// Memory Usage: 15.4 MB, less than 8.57% of C online submissions for Network Delay Time.

// 해시테이블 이용해서 풀어보기 (val 필드 없애고 index 이용)
// dijkstra로 풀어보기
#define MAX_TIME 2147483637

enum VisitMode { NotVisited, Visited };

typedef struct vertex
{
    int             val;
    int             visited;
    int             time;
    struct edge*    adjacency;
    struct vertex*  next;
}   Vertex;

typedef struct edge
{
    int             weight;
    Vertex*         to;
    struct edge*    next;
}   Edge;

typedef struct graph
{
    Vertex* vertices;
    int     size;
}   Graph;

typedef struct heap
{
    int*    times;
    int     size;
}   Heap;

Vertex* createVertex(int val)
{
    Vertex* V;
    
    V = (Vertex*)calloc(1, sizeof(Vertex));
    V->val = val;
    V->visited = NotVisited;
    V->time = MAX_TIME;
    return (V);
}

Edge*   createEdge(int weight, Vertex* V)
{
    Edge*   E;
    
    E = (Edge*)calloc(1, sizeof(Edge));
    E->weight = weight;
    E->to = V;
    return (E);
}

// val 값을 가지는 정점 찾기
Vertex* findVertex(Graph G, int val)
{
    Vertex* V;
    
    V = G.vertices;
    while (V != NULL)
    {
        if (V->val == val)
            return (V);
        V = V->next;
    }
    return (NULL);
}

// weight 오름차순으로 정렬되도록 추가 -> 런타임이 2~3배 빨라지더라고요..
void    addPath(Vertex* V, Edge* E)
{
    Edge*   curr;
    
    curr = V->adjacency;
    if (curr == NULL)
    {
        V->adjacency = E;
        return ;
    }
    if (curr->weight >= E->weight)
    {
        E->next = curr;
        V->adjacency = E;
        return ;
    }
    while (curr->next != NULL && curr->next->weight < E->weight)
        curr = curr->next;
    E->next = curr->next;
    curr->next = E;
}

// 그래프에 정점 추가
Vertex* addVertex(Graph* G, Vertex* new)
{
    Vertex* curr;
    
    curr = G->vertices;
    (G->size)++;
    if (curr == NULL)
    {
        G->vertices = new;
        return (new);
    }
    new->next = curr;
    G->vertices = new;
    return (new);
}

void    getTime(Vertex* V, int weight)
{
    Edge*   adjacency;
    
    adjacency = V->adjacency;
    if (V->time <= weight)  // 현재 입력된 시간보다 작은 경우만 수행
        return ;
    V->time = weight;
    while (adjacency != NULL)
    {
        getTime(adjacency->to, weight + adjacency->weight);
        adjacency = adjacency->next;
    }
}

// 흔한 힙 삽입 연산
void    HEAP_insert(Heap* H, int time)
{
    int parent;
    int curr;
    int tmp;
    
    curr = (H->size)++;
    H->times[curr] = time;
    while (curr > 0)
    {
        parent = (curr - 1) / 2;
        if (H->times[parent] < time)
            break ;
        tmp = H->times[curr];
        H->times[curr] = H->times[parent];
        H->times[parent] = tmp;
        curr = parent;
    }
}

// 흔한 힙 삭제 연산
int HEAP_getMin(Heap* H)
{
    int min;
    int left_child;
    int smaller_child;
    int curr;
    int tmp;
    
    if (H->size == 0)
        return (-1);
    min = H->times[0];
    H->times[0] = H->times[--(H->size)];
    H->times[H->size] = MAX_TIME;
    curr = 0;
    while (curr <= H->size)
    {
        left_child = curr * 2 + 1;
        if (left_child > H->size)   // 자식이 없는 경우
            break ;
        if (left_child + 1 > H->size)   // 자식이 하나인 경우
            smaller_child = left_child;
        else
        {
            if (H->times[left_child] > H->times[left_child + 1])
                smaller_child = left_child + 1;
            else
                smaller_child = left_child;
        }
        if (H->times[curr] < H->times[smaller_child])
            break ;
        tmp = H->times[curr];
        H->times[curr] = H->times[smaller_child];
        H->times[smaller_child] = tmp;
        curr = smaller_child;
    }
    return (min);
}

void initGraph(Graph* G, int** times, int timesSize)
{
    Vertex* from;
    Vertex* to;
    
    for (int i = 0; i < timesSize; i++)
    {
        from = findVertex(*G, times[i][0]);
        if (from == NULL)
            from = addVertex(G, createVertex(times[i][0]));
        to = findVertex(*G, times[i][1]);
        if (to == NULL)
            to = addVertex(G, createVertex(times[i][1]));
        addPath(from, createEdge(times[i][2], to));
    }
}

int networkDelayTime(int** times, int timesSize, int* timesColSize, int n, int k){
    Graph   G;
    Vertex* begin;
    Vertex* curr;
    int     time;
    Heap    H;
    
    G.vertices = NULL;
    G.size = 0;
    if (n == 1)
        return (0);
    initGraph(&G, times, timesSize);
    getTime(findVertex(G, k), 0);

    H.times = (int*)malloc(sizeof(int) * G.size);
    H.size = 0;
    curr = G.vertices;
    while (curr != NULL)
    {
        HEAP_insert(&H, curr->time);
        curr = curr->next;
    }
    for(int i = 0; i < n; i++)
        time = HEAP_getMin(&H);
    if (time == MAX_TIME)
        return (-1);

    return (time);
}