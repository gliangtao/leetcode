#include <stdlib.h>


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>

#ifdef MY_UNIT_TEST

int** threeSum(int* nums, int numsSize, int* returnSize);

int NA[] = { -4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6 };

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int retSize;
    gettimeofday(&tvStart, NULL);
    threeSum(NA, sizeof(NA) / sizeof(NA[0]), &retSize);
    gettimeofday(&tvEnd, NULL);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, threeSum\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#endif

#include <stdlib.h>

#ifdef MY_UNIT_TEST
#define DBG(str...) printf(str)
#else
#define DBG(str...)
#endif

typedef struct MyNode {
    int v[3];
    struct MyNode* next;
} MyNode;

static int** myConvert(MyNode* head, int size) {
    if (!head || !size) {
        return NULL;
    }
    int** ret = (int**)malloc(sizeof(int*) * size);
    if (ret) {
        int** pret = ret;
        MyNode* p = head;
        while (p != NULL) {
            *pret++ = p->v;
            p = p->next;
        }
    }
    return ret;
}

static int mycmp(const void* p1, const void* p2) {
    //DBG("p1 %d, p2 %d\n", *((int*)p1), *((int*)p2));
    return (*((int*)p1) - *((int*)p2));
}

/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize) {
    int *p, *q, *r, *pl, *pr;
    p = nums;
    r = nums + (numsSize - 1);
    int target;
    MyNode* head = NULL;
    *returnSize = 0;
    if (!nums || (numsSize < 3)) {
        return NULL;
    }
    int **tps = (int**)malloc(sizeof(int*) * numsSize);
    if (!tps) {
        return NULL;
    }
    int **ptps = tps;
    int ntps = 0;
    qsort(nums, numsSize, sizeof(int), mycmp);
    DBG("Sorted nums:");
    for (int i = 0; i < numsSize; i++) {
        DBG(",%d", nums[i]);
    }
    DBG("\n");
    int vj;
    for (int j = numsSize - 1, vj = nums[j]; j > 1;) {
        target = -vj;
        p = nums;
        r = nums + j - 1;
        int v = *p + *r;
        int vp;
        int vr;
        DBG("r %d, target %d\n", j, target);
        while (p < r) {
            if (v < target) {
                vp = *p;
                while ((p < r) && (vp == *(++p)));
                DBG("New p %ld, new vp %d\n", p-nums, *p);
            } else if (v > target) {
                vr = *r;
                while ((p < r) && (vr == *(--r)));
                DBG("New r %ld, new vr %d\n", r-nums, *r);
            } else {
                MyNode* tmp = (MyNode*)malloc(sizeof(MyNode));
                if (!tmp) {
                    break;
                }
                tmp->next = head;
                head = tmp;
                head->v[0] = *p;
                head->v[1] = *r;
                head->v[2] = vj;
                ntps++;
                DBG("Got match: %d, %d, %d, p %ld, r %ld, j %d\n", *p, *r, vj, p-nums, r-nums, j);
                vp = *p;
                while ((p < r) && (vp == *(++p)));
                vr = *r;
                while ((p < r) && (vr == *(--r)));
            }
            v = *p + *r;
            DBG("New v %d, target %d\n", v, target);
        }
        while ((j > 1) && (nums[--j] == vj));
        vj = nums[j];
    }
    *returnSize = ntps;
    DBG("Total %d matched triplets\n", *returnSize);
    return myConvert(head, ntps);
}
