/**
Given a binary tree, return the level order traversal of its nodes' values.
(ie, from left to right, level by level).

For example:
Given binary tree {3,9,20,#,#,15,7},
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
//4ms
int** levelOrder(struct TreeNode* root, int** columnSizes, int* returnSize) {
    if (!root) return NULL;
    int ccap = 1024;
    int rcap = 1024;
    struct TreeNode** q = NULL;
    int* csize = NULL;
    int** ret = NULL;
    ret = (int**)malloc(sizeof(int*) * ccap);
    csize = (int*)malloc(sizeof(int) * ccap);
    q = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * ccap);
    int qt, qh, qt_saved, qsize = 1024, icols, i;
    struct TreeNode *p;

    if (!ret || !q) goto bail;
    qh = qt = 0;
    q[qt++] = root;
    icols = 0;
    while (qh != qt) {
        int* buf = (int*)malloc(sizeof(int) * rcap);
        if (!buf) break;
        qt_saved = qt;
        for (i = 0; qh != qt_saved; i++) {
            p = q[qh];
            buf[i] = p->val;
            if (p->left) {
                q[qt] = p->left;
                qt++;
                if (qt >= ccap) qt -= ccap;
            }
            if (p->right) {
                q[qt] = p->right;
                qt++;
                if (qt >= ccap) qt -= ccap;
            }
            qh++;
            if (qh >= ccap) qh -= ccap;
        }
        ret[icols] = realloc(buf, i * sizeof(int));
        csize[icols++] = i;
    }

bail:
    free(q);
    ret = realloc(ret, icols * sizeof(int*));
    csize = realloc(csize, icols * sizeof(int));
    *columnSizes = csize;
    *returnSize = icols;

    return ret;
}
