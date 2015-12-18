/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
//0ms O(n) solution
int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    const int RSIZE = 1024;
    if (!root) return NULL;
    int* ret = (int*)malloc(sizeof(int) * 1024);
    if (!ret) return NULL;
    int* p = ret, *end = ret + RSIZE - 1;
    struct TreeNode* s[1024];
    int top = 0, rsize;
    struct TreeNode* node;
    node = root;
    while ((top >= 0) && (p <= end)) {
        if (!node) {
            if (top == 0) break;
            node = s[--top]->right;
        } else {
            *p++ = node->val;
            s[top++] = node;
            node = node->left;
        }
    }
    *returnSize = (int)(p - ret);
    return ret;
}
