typedef struct node {
    int val;
    struct node *left;
    struct node *right;
 } Node;

Node* createNode(int data)
{
    Node* node;
    
    node = (Node*)malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->val = data;
    return (node);
}

// 트리에 노드를 추가
void insertNode(Node** root, Node* newNode)
{
    if (!(*root))  // 트리가 비었으면 루트에 삽입
    {
        *root = newNode;
        return ;
    }
    if ((*root)->val > newNode->val)  // 루트보다 작으면 왼쪽 하위 트리에 삽입
    {
        if ((*root)->left == NULL)
            (*root)->left = newNode;
        else
            insertNode(&((*root)->left), newNode);
    }
    else  // 루트보다 크면 오른쪽 하위 트리에 삽입
    {
        if ((*root)->right == NULL)
            (*root)->right = newNode;
        else
            insertNode(&((*root)->right), newNode);
    }
}

/**
 * 정렬된 배열이므로 가운데 값을 추가하고 왼쪽 오른쪽 나눠서 재귀 호출..
 * 계속 중간값이 추가되므로 높이 균형을 맞출 수 있음
 * (퀵정렬을 떠올려보세용)
 */
void partition(Node** tree, int* nums, int start, int end)
{
    if (end - start > 1)
    {
        insertNode(tree, createNode(nums[start + (end - start) / 2]));
        partition(tree, nums, start, start + (end - start) / 2 - 1);
        partition(tree, nums, start + (end - start) / 2 + 1, end);
    }
    else
    {
        if (start != end)
            insertNode(tree, createNode(nums[start]));
        insertNode(tree, createNode(nums[end]));
    }
}

Node* sortedArrayToBST(int* nums, int numsSize){
    Node* root;
    
    root = NULL;
    partition(&root, nums, 0, numsSize - 1);
    return (root);
}