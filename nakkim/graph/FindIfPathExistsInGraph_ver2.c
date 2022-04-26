// Edge 구조체를 만드는 대신, 정수형 배열을 재할당 해가면서 사용해봤다.
// ver1과는 Adjacency 추가 부분만 다르다.
// 재할당은 느리다.. 쓰지말자
// 703 ms, faster than 27.27%
// 91.8 MB, less than 6.06%

enum VisitMode { NotVisited, Visited };

typedef struct vertex
{
    int     visited;
    int*    adjacency_list;
    int     adjacency_size;
}   Vertex;

typedef struct graph
{
    Vertex* vertices;
    int     size;
}   Graph;

void    putAdjacency(Graph* G, int from, int to)
{
    if (G->vertices[from].adjacency_list == NULL)
    {
        G->vertices[from].adjacency_list = (int*)malloc(sizeof(int));
        G->vertices[from].adjacency_list[(G->vertices[from].adjacency_size)++] = to;
    }
    else
    {
        G->vertices[from].adjacency_list = (int*)realloc(G->vertices[from].adjacency_list, sizeof(int) * ++(G->vertices[from].adjacency_size));
        G->vertices[from].adjacency_list[G->vertices[from].adjacency_size - 1] = to;
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
    int to;
    
    G->vertices[from].visited = Visited;
    if (from == destination)
        return (true);
    for (int i = 0; i < G->vertices[from].adjacency_size; i++)
    {
        to = G->vertices[from].adjacency_list[i];
        if (G->vertices[to].visited == NotVisited && DFS(G, to, destination))
            return (true);
    }
    return (false);
}

void    freeAll(Graph G)
{
    for (int i = 0; i < G.size; i++)
        free(G.vertices[i].adjacency_list);
    free(G.vertices);
}

bool validPath(int n, int** edges, int edge_size, int* edgesColSize, int source, int destination){
    Graph   G;
    bool    result;
    
    if (source == destination)
        return (true);
    G.size = n;
    G.vertices = (Vertex*)calloc(n, sizeof(Vertex));
    getAdjacencyList(&G, edges, edge_size);
    result = DFS(&G, source, destination);
    freeAll(G);
    return (result);
}