#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>
#ifdef MY_UNIT_TEST
#define DBG(str...) printf(str)

//int C[] = { 1, 2 };
//int T = 1;
//int C[] = { 2, 3, 5 };
//int T = 7;
//int C[] = { 1 };
//int T = 1;
//int C[] = {1, 2};
//int T = 2;
//int C[] = { 8,7,4,3 };
//int T = 11;
//int C[] = { 7,3,9,6 };
//int T = 6;
//int C[] = {2, 2, 2};
//int T = 4;
//int C[] = {3,1,3,5,1,1};
//int T = 8;
int C[] = { 10,1,2,7,6,1,5 };
int T = 8;

int** combinationSum2(int* candidates, int candidatesSize, int target, int** columnSizes, int* returnSize);
int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int retSize, *colSizes;
    gettimeofday(&tvStart, NULL);
    combinationSum2(C, sizeof(C) / sizeof(C[0]), T, &colSizes, &retSize);
    gettimeofday(&tvEnd, NULL);
    printf("Found %d combinations for target %d\n", retSize, T);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    DBG("Time %d.%06d, combinationSum\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif

/*
Given a collection of candidate numbers (C) and a target number (T), find all unique combinations
in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

Note:
All numbers (including target) will be positive integers.
Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
The solution set must not contain duplicate combinations.
For example, given candidate set 10,1,2,7,6,1,5 and target 8, 
A solution set is: 
[1, 7] 
[1, 2, 5] 
[2, 6] 
[1, 1, 6] 
*/
#include <stdlib.h>

typedef struct MyNode {
    struct MyNode*  next;
    int*            cmb;
    int             cmbSize;
} MyNode;

//4ms version
static int rfun(int* c, int* f, int n, int target, MyNode** head, int count) {
    int cv = *c;
    if ((cv > target) || (n < 0)) {
        breakme();
        return 0;
    }
    int sum = 0;
    if (!n || (target == cv)) {
        breakme();
        if (target != cv) return 0;
        MyNode* node = (MyNode*)malloc(sizeof(MyNode));
        if (node) {
            int total = count + 1;
            int* match = (int*)malloc(sizeof(int) * total);
            if (match) {
                int* pf;
                int* pc;
                node->next = *head;
                node->cmb = match;
                node->cmbSize = total;
                *f = 1;
                int* p = match + total;
                for (pf = f, pc = c; total > 0; pf--, pc--) {
                    int i = *pf;
                    total -= i;
                    for (; i > 0; i--) {
                        *(--p) = *pc;
                    }
                }
                total = node->cmbSize;
                #ifdef MY_UNIT_TEST
                static int ID = 0;
                printf("CMB %d count %d:", ID++, total);
                for (int i = 0; i < total; i++) {
                    printf(",%d", node->cmb[i]);
                }
                printf("\n");
                #endif
                MyNode* prev = *head;
                DBG("Curr %p cmbSize %d\n", node, total);
                DBG("Prev %p cmbSize %d\n", prev, prev ? prev->cmbSize : 0);
                while (prev != NULL) {
                    if ((prev->cmbSize == total) && !memcmp(prev->cmb, match, total * sizeof(int))) {
                        DBG("Duplicate result detected, discarding...\n");
                        free(match);
                        free(node);
                        return 0;
                    }
                    prev = prev->next;
                }
                *head = node;
                sum = 1;
                DBG("Good result detected, collecting...\n");
            } else {
                free(node);
            }
        }
        return sum;
    }
    {
        int nt = target - cv;
        if (cv <= target) {
            if (c[1] <= nt) {
                *f = 1;
                sum = rfun(c + 1, f + 1, n - 1, nt, head, count + 1);
            }
            *f = 0;
            sum += rfun(c + 1, f + 1, n - 1, target, head, count);
        }/*
        *f = 1;
        sum = rfun(c + 1, f + 1, n - 1, nt, head, count + 1);
        *f = 0;
        sum += rfun(c + 1, f + 1, n - 1, target, head, count);*/
    }
    return sum;
}

static int mycmp(const void* p1, const void* p2) {
    return (*((int*)p1) - *((int*)p2));
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
//8ms version
int** combinationSum2(int* candidates, int candidatesSize, int target, int** columnSizes, int* returnSize) {
    int* colSizes = NULL;
    int** ret = 0;
    int nRet = 0;
    MyNode* head = NULL;
    int* factors = NULL;
    if (!candidates || !candidatesSize) {
        goto bail;
    }

    qsort(candidates, candidatesSize, sizeof(candidates[0]), mycmp);
    #ifdef MY_UNIT_TEST
    static int ID = 0;
    printf("Sorted candidates (%d):", candidatesSize);
    for (int i = 0; i < candidatesSize; i++) {
        printf(",%d", candidates[i]);
    }
    printf("\n");
    #endif

    if (candidates[0] <= target) {
        factors = (int*)malloc(sizeof(int) * candidatesSize);
        if (!factors) goto bail;
        memset(factors, 0, sizeof(int) * candidatesSize);

        nRet = rfun(candidates, factors, candidatesSize - 1, target, &head, 0);
        if (nRet > 0) {
            int** p = ret;
            int* psize = colSizes;
            p = (int**)malloc(sizeof(int*) * nRet);
            psize = (int*)malloc(sizeof(int) * nRet);
            if (!p || !psize) {
                free(ret);
                free(colSizes);
                ret = NULL;
                colSizes = NULL;
                nRet = 0;
                goto bail;
            }
            ret = p;
            colSizes = psize;
            MyNode* cur = head, *next;
            while (cur != NULL) {
                next = cur->next;
                *p++ = cur->cmb;
                *psize++ = cur->cmbSize;
                free(cur);
                cur = next;
            }
            nRet = p - ret;
        }
    }

bail:
    DBG("nRet %d\n", nRet);
    free(factors);
    *returnSize = nRet;
    *columnSizes = colSizes;
    return ret;
}
