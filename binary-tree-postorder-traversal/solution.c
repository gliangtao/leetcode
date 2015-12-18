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
#if 0
//0ms version
int* postorderTraversal(struct TreeNode* root, int* returnSize) {
    if (!root) return NULL;
    struct TreeNode* s[1024], *node;
    int rcap = 1024, top, rsize = 0, *p;
    int* ret = (int*)malloc(rcap * sizeof(int));
    if (!ret) return NULL;

    s[top = 0] = root;
    p = ret;
    while (top >= 0) {
        if (rsize == rcap) {
            rcap <<= 1;
            int* buf = (int*)realloc(ret, rcap * sizeof(int));
            if (!buf) {
                *returnSize = rcap;
                return ret;
            }
        }
        node = s[top];
        if (node->left) {
            s[++top] = node->left;
        } else if (node->right) {
            s[++top] = node->right;
        } else {
            *p++ = node->val;
            top--;
            while ((top >= 0) && ((s[top + 1] == s[top]->right) || (NULL == s[top]->right))) {
                *p++ = s[top--]->val;
            }
            if (top >= 0) {
                s[top + 1] = s[top]->right;
                top++;
            }
        }
    }
    *returnSize = (int)(p - ret);
    return ret;
}
#endif

//0ms version
int* postorderTraversal(struct TreeNode* root, int* returnSize) {
    if (!root) return NULL;
    struct TreeNode* s[1024], *node;
    int rcap = 1024, top, rsize = 0, *p;
    int* ret = (int*)malloc(rcap * sizeof(int));
    if (!ret) return NULL;

    s[top = 0] = root;
    node = root->left;
    p = ret;

    while (top >= 0) {
        if (node != NULL) {
            s[++top] = node;
            node = node->left;
        } else if (NULL != s[top]->right) {
            node = s[top]->right;
        } else {
            s[top + 1] = NULL;
            while ((top >= 0) && (s[top + 1] == s[top]->right)) {
                *p++ = s[top--]->val;
            }
            if (top >= 0) node = s[top]->right;
        }
    }

    *returnSize = (int)(p - ret);
    ret = (int*)realloc(ret, (int)(p - ret) * sizeof(int));
    return ret;
}
