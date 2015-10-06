/*
 * Given an array S of n integers, are there elements a, b, c, and d in S such that
 * a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note:
Elements in a quadruplet (a,b,c,d) must be in non-descending order. (ie, a ≤ b ≤ c ≤ d)
The solution set must not contain duplicate quadruplets.
    For example, given array S = {1 0 -1 0 -2 2}, and target = 0.

    A solution set is:
    (-1,  0, 0, 1)
    (-2, -1, 1, 2)
    (-2,  0, 0, 2)
*/

#include <stdlib.h>

typedef struct MyNode {
    int v[4];
    struct MyNode* next;
} MyNode;

static int** convertNodes(MyNode* head, int size) {
    if (!head || !size) {
        return NULL;
    }
    int** ret = (int**)malloc(sizeof(int*) * size);
    int** p = ret;
    if (ret) {
        while (head != NULL) {
            *p++ = head->v;
            head = head->next;
        }
    }
    return ret;
}

int mycmp(const void* p1, const void* p2) {
    return (*((int*)p1) - *((int*)p2));
}


// This is one 32ms version
/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int** fourSum(int* nums, int numsSize, int target, int* returnSize) {
    int nRet = 0;
    MyNode* head = NULL;
    int *p1, *p2, *p3, *p4, *end;
    int v1, v2, v3, v4;
    if (!nums || (numsSize < 4)) {
        if (returnSize) *returnSize = 0;
        return NULL;
    }
    qsort(nums, numsSize, sizeof(int), mycmp);

    end = nums + numsSize - 1;
    int vdelta;
    for (p1 = nums, v1 = *p1; p1 <= end - 3;) {
        v1 = *p1;
        for (p2 = p1 + 1, v2 = *p2; p2 <= end - 2;) {
            vdelta = v1 + v2 - target;
            for (p3 = p2 + 1, p4 = end, v3 = *p3, v4 = *p4; p3 < p4;) {
                int delta = v3 + v4 + vdelta;
                if (delta < 0) {
                    while ((p3 < p4) && (v3 == *(++p3)));
                    v3 = *p3;
                } else if (delta > 0) {
                    while ((p3 < p4) && (v4 == *(--p4)));
                    v4 = *p4;
                } else {
                    MyNode* tmp = (MyNode*)malloc(sizeof(MyNode));
                    if (!tmp) {
                        goto bail;
                    }
                    tmp->v[0] = v1;
                    tmp->v[1] = v2;
                    tmp->v[2] = v3;
                    tmp->v[3] = v4;
                    tmp->next = head;
                    head = tmp;
                    nRet++;

                    while ((p3 < p4) && (v3 == *(++p3)));
                    v3 = *p3;
                    while ((p3 < p4) && (v4 == *(--p4)));
                    v4 = *p4;
                }
            }
            while ((p2 < p3) && (v2 == *(++p2)));
            v2 = *p2;
        }
        while ((p1 < p2) && (v1 == *(++p1)));
        v1 = *p1;
    }
bail:
    if (returnSize) *returnSize = nRet;
    return convertNodes(head, nRet);
}
