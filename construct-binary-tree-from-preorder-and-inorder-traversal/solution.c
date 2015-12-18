/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
static struct TreeNode* mkNode(int val, struct TreeNode* left, struct TreeNode* right) {
    struct TreeNode* ret = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (ret) {
        ret->val = val;
        ret->left = left;
        ret->right = right;
    } else {
        printf("Error allocating TreeNode\n");
    }
    return ret;
}

//20ms, recursive
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    if (!preorder || !inorder || (preorderSize != inorderSize) || !inorderSize) return NULL;
    if (inorderSize == 1) return mkNode(*inorder, NULL, NULL);
    int i;
    int val = *preorder;
    for (i = 0; inorder[i] != val; i++);
    struct TreeNode* left, *right;
    left = buildTree(preorder + 1, i, inorder, i);
    right = buildTree(preorder + i + 1, preorderSize - i - 1, inorder + i + 1, inorderSize - i - 1);
    return mkNode(val, left, right);
}
