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

struct Interval {
    int start;
    int end;
};

struct Interval* merge(struct Interval* intervals, int intervalsSize, int* returnSize);
static struct Interval N[] =
//{ { 1, 4} , {0, 0} };
{ {1,4}, {0,2},{3,5}};
//{{2,3},{4,5},{6,7},{8,9},{1,10}};


int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    struct Interval* retVal;
    int retSize;
    printf("Before merge: size %d\n", (int)(sizeof(N) / sizeof(N[0])));
    for (int i = 0; i < sizeof(N) / sizeof(N[0]); i++) printf(",[%d,%d]", N[i].start, N[i].end);
    printf("\n");
    gettimeofday(&tvStart, NULL);
    retVal = merge(N, sizeof(N) / sizeof(N[0]), &retSize);
    gettimeofday(&tvEnd, NULL);
    
    printf("After merge: size %d\n", retSize);
    for (int i = 0; i < retSize; i++) printf(",[%d,%d]", retVal[i].start, retVal[i].end);
    printf("\n");
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, merge\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif
/*
Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18].
*/

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 * };
 */
static void myqsort(struct Interval* intervals, int l, int r) {
    if (l >= r) return;
    int m = (l + r + 1) >> 1;
    struct Interval x = intervals[m];
    intervals[m] = intervals[r];
    struct Interval t;
    int i, j;

#if 1
    //This version might swap less times for nearly-sorted arrays
    for (i = l, j = r - 1; i < j; i++) {
        if (intervals[i].start > x.start) {
            for (; j > i; j--) {
                if (intervals[j].start <= x.start) {
                    t = intervals[j];
                    intervals[j] = intervals[i];
                    intervals[i] = t;
                    break;
                }
            }
        }
    }
    m = (intervals[j].start > x.start) ? j : (j + 1);
#else
    //This version might swap more times for nearly-sorted arrays
    for (i = l, j = l; i < r; i++) {
        if (intervals[i].start <= x.start) {
            t = intervals[j];
            intervals[j] = intervals[i];
            intervals[i] = t;
            j++;
        }
    }
    m = j;
#endif

    intervals[r] = intervals[m];
    intervals[m] = x;
    myqsort(intervals, l, m - 1);
    myqsort(intervals, m + 1, r);
}

static int mycmp(const void* param1, const void* param2) {
    struct Interval* p1 = (struct Interval*)param1;
    struct Interval* p2 = (struct Interval*)param2;
    return (p1->start - p2->start);
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
//568ms version
struct Interval* merge(struct Interval* intervals, int intervalsSize, int* returnSize) {
    if (!intervals || !intervalsSize) return NULL;
    int retSize = 0;
    struct Interval* ret = (struct Interval*)malloc(sizeof(struct Interval) * intervalsSize);
    if (ret) {
        struct Interval *p, *q, *end;
        //myqsort(intervals, 0, intervalsSize - 1);
        qsort(intervals, intervalsSize, sizeof(struct Interval), mycmp);
        *ret = *intervals;
        for (p = ret, q = intervals + 1, end = intervals + intervalsSize; q < end; q++) {
            if (p->end >= q->start) {
                if (p->end < q->end) p->end = q->end;
            } else {
                *(++p) = *q;
            }
        }
        retSize = (int)(p - ret + 1);
    }
    if (returnSize) *returnSize = retSize;
    return ret;
}
