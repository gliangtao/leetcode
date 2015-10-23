
#include <stdlib.h>
#include <limits.h>

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
#define bool    int
#define true    1
#define false   0

int** permuteUnique(int* nums, int numsSize, int* returnSize);

//int N[] = {1,1,2};
int N[] =
//{2,2,1,1};
{0,1,0,0,9};

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int retSize;
    gettimeofday(&tvStart, NULL);
    permuteUnique(N, sizeof(N) / sizeof(N[0]), &retSize);
    gettimeofday(&tvEnd, NULL);
    
    printf("permute: %d\n", retSize);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    DBG("Time %d.%06d, permute\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif

/*
Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[1,1,2], [1,2,1], and [2,1,1].
*/

#include <stdlib.h>
#include <string.h>

typedef struct MyNode {
    struct MyNode*  next;
    int*            na;
} MyNode;

static int mySub(int* nums, int iStart, int iEnd, MyNode** head) {
    if (iStart == iEnd) {
        // No changes, nums are fixed
        int* na = (int*)malloc(sizeof(int) * (iEnd + 1));
        MyNode* node = (MyNode*)malloc(sizeof(MyNode));
        if (!na || !node) {
            free(na);
            free(node);
            return 0;
        }
        memcpy(na, nums, sizeof(int) * (iEnd + 1));
        node->na = na;
        node->next = *head;
        *head = node;
        #ifdef MY_UNIT_TEST
        static int count = 0;
        printf("P %04d: ", count++);
        for (int i = 0; i <= iEnd; i++) {
            printf(",%d", na[i]);
        }
        printf("\n");
        #endif
        return 1;
    }

    int t, lastNum, ret = 0;
    const int N = iEnd - iStart;
    int used[N];
    int iUsed = -1;


    lastNum = t = nums[iStart];
    ret += mySub(nums, iStart + 1, iEnd, head);
    used[++iUsed] = t;
    for (int j = iStart + 1; j <= iEnd; j++) {
        int nj = nums[j];
        int needSkip = 0;
        for (int i = 0; i <= iUsed; i++) {
            if (used[i] == nj) {
                needSkip = 1;
                break;
            }
        }
        if (!needSkip) {
            used[++iUsed] = nj;
            nums[iStart] = nj;
            nums[j] = t;

            ret += mySub(nums, iStart + 1, iEnd, head);

            nums[j] = nj;
            nums[iStart] = t;
        }
    }

    return ret;
}

static int mycmp(const void* p1, const void* p2) {
    return (*((int*)p1) - *((int*)p2));
}

/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
//12ms version
int** permuteUnique(int* nums, int numsSize, int* returnSize) {
    if (!nums || !numsSize) return NULL;
    int retSize;
    MyNode* head = NULL;
    MyNode* pNode;
    int** ret = NULL;
    int i;

    //qsort should not be needed in this problem
    //qsort(nums, numsSize, sizeof(int), mycmp);

    retSize = mySub(nums, 0, numsSize - 1, &head);
    ret = (int**)malloc(sizeof(int*) * retSize);
    if (!ret) goto bail;

    int** p = ret + retSize - 1;

    while (head != NULL) {
        pNode = head->next;
        *p-- = head->na;
        free(head);
        head = pNode;
    }

    if (returnSize != NULL) *returnSize = retSize;

bail:
    return ret;
}
