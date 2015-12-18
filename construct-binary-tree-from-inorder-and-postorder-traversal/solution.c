/**
Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.
*/
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
    }
    return ret;
}

//24ms
struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {
    if (!inorder || !postorder || (inorderSize != postorderSize) || !inorderSize) return NULL;
    if (inorderSize == 1) return mkNode(*inorder, NULL, NULL);
    struct TreeNode* left, *right;
    int i, val;
    val = postorder[postorderSize - 1];
    for (i = 0; inorder[i] != val; i++);
    left = buildTree(inorder, i, postorder, i);
    right = buildTree(inorder + i + 1, inorderSize - i - 1, postorder + i, inorderSize - i - 1);
    return mkNode(val, left, right);
}
