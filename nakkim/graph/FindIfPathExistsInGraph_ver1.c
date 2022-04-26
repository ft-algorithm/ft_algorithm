// 정점 값의 범위가 [0,n-1] 이므로 값을 인덱스로 사용함
// 626 ms, faster than 36.36%
// 81.2 MB, less than 6.06%

enum VisitMode { NotVisited, Visited };

typedef struct vertex
{
    int             visited;
    struct edge*    adjacency_list;
}   Vertex;

typedef struct edge
{
    int             to;
    struct edge*    next;
}   Edge;

typedef struct graph
{
    Vertex* vertices;
    int     size;
}   Graph;

Edge*   createEdge(int to)
{
    Edge*   e;
    
    e = (Edge*)malloc(sizeof(Edge));
    e->to = to;
    e->next = NULL;
    return (e);
}

// 인접 리스트 추가
void    putAdjacency(Graph* G, int from, int to)
{
    Edge*   curr;
    Edge*   new_edge;
    
    curr = G->vertices[from].adjacency_list;
    new_edge = createEdge(to);
    if (curr == NULL)
        G->vertices[from].adjacency_list = new_edge;
    else
    {
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = new_edge;
    }
}

void    getAdjacencyList(Graph* G, int** edges, int edge_size)
{
    for (int i = 0; i < edge_size; i++)
    {
        putAdjacency(G, edges[i][0], edges[i][1]);
        putAdjacency(G, edges[i][1], edges[i][0]);
    }
}

bool    DFS(Graph* G, int from, int destination)
{
    Edge*   adjacency;
    
    adjacency = G->vertices[from].adjacency_list;
    G->vertices[from].visited = Visited;
    if (from == destination)
        return (true);
    while (adjacency != NULL)
    {
        // 다음 인접 정점이 방문되지 않은 것이면 ㄱ ㄱ
        if (G->vertices[adjacency->to].visited == NotVisited && DFS(G, adjacency->to, destination))
            return (true);
        adjacency = adjacency->next;
    }
    return (false);
}

void    freeAll(Graph G)
{
    Edge*   remove;
    
    for (int i = 0; i < G.size; i++)
    {
        remove = G.vertices[i].adjacency_list;
        while (remove != NULL)
        {
            G.vertices[i].adjacency_list = remove->next;
            free(remove);
            remove = G.vertices[i].adjacency_list;
        }
    }
    free(G.vertices);
}

bool validPath(int n, int** edges, int edge_size, int* edgesColSize, int source, int destination){
    Graph   G;
    bool    result;
    
    if (source == destination)
        return (true);
    G.size = n;
    G.vertices = (Vertex*)calloc(n, sizeof(Vertex));    // visited는 Notvisited, 인접 리스트는 NULL로 초기화
    getAdjacencyList(&G, edges, edge_size);
    result = DFS(&G, source, destination);
    freeAll(G);
    return (result);
}