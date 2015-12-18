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
int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    if (!root) return NULL;
    int rcap = 1024, rsize = 0, SZ = 1024;
    struct TreeNode* s[SZ], *node;
    int top;
    int* ret = (int*)malloc(rcap * sizeof(int)), *p;
    if (!ret) return NULL;

    top = 0;
    node = root;

    while (top >= 0) {
        if (rsize >= rcap) {
            rcap <<= 1;
            int* nbuf = (int*)realloc(ret, rcap * sizeof(int));
            if (!nbuf) {
                *returnSize = rcap;
                return ret;
            }
        }
        if (!node) {
            if (top == 0) break;
            node = s[--top];
            ret[rsize++] = node->val;
            node = node->right;
        } else {
            s[top++] = node;
            node = node->left;
        }
    }

    *returnSize = rsize;
    return ret;
}
