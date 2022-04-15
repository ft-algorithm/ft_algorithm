#include <stdlib.h>

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};
 

struct TreeNode *create_node(int num)
{
    struct TreeNode *new;
    
    new = calloc(sizeof(struct TreeNode), 1);
    if (!new)
        exit(0);
    new->val = num;
    return (new);
}


/* 
새로운 노드 위치 찾는 함수
*/
void    next_node(struct TreeNode *root, int *nums, int mid)
{
    struct TreeNode *temp;

    temp = root;
    while (nums[mid] != temp->val)
    {
        if (nums[mid] > temp->val)
        {
            if (temp->right)
                temp = temp->right;
            else
            {
                temp->right = create_node(nums[mid]);
                break;
            }
        }
        else if (nums[mid] < temp->val)
        {
            if (temp->left)
                temp = temp->left;
            else
            {
                temp->left = create_node(nums[mid]);
                break;
            }
        }
    }
}

/*
    트리 만드는 함수
    절반씩 잘라서 재귀호출
    노드 위치 찾고 반 잘라서 다시 호출하고...반복
*/
void    make_tree(struct TreeNode *root, int *nums, int start, int end)
{
	if (end <= start)
		return ;
    next_node(root, nums, (end + start) / 2);
    //차이가 1 이하면 리턴시켜줘야 함. 안그러면 무한루프
    if (end - start <= 1)
        return ;
    make_tree(root, nums, start, start + (end - start) / 2);
    make_tree(root, nums, start + (end - start) / 2, end);
}

struct TreeNode* sortedArrayToBST(int* nums, int numsSize){
    struct TreeNode *root;
    int             mid;

    mid = numsSize / 2;
    root = create_node(nums[mid]);
	make_tree(root, nums, 0, numsSize);
    return (root);
}
