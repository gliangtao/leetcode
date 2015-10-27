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

int maxSubArray(int* nums, int numsSize);

static int N[] =
//{1, 2};
{-2,1,-3,4,-1,2,1,-5,4};

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int retSize;
    gettimeofday(&tvStart, NULL);
    retSize = maxSubArray(N, sizeof(N) / sizeof(N[0]));
    gettimeofday(&tvEnd, NULL);
    
    printf("maxSubArray: %d\n", retSize);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, maxSubArray\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif

/*
Find the contiguous subarray within an array (containing at least one number) which has the
largest sum.

For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
the contiguous subarray [4,−1,2,1] has the largest sum = 6.

click to show more practice.

More practice:
If you have figured out the O(n) solution, try coding another solution using the divide and conquer
approach, which is more subtle.
*/
//4ms version
int maxSubArray(int* nums, int numsSize) {
    if (!nums || (numsSize <= 0)) return INT_MIN;

    int v, sum, sum2, maxSum;
    int* p, *pend;

    p = nums;
    pend = nums + numsSize;
    maxSum = INT_MIN;
    sum = 0;

    while (p < pend) {
        v = *p++;
        sum += v;
        if (maxSum < sum) maxSum = sum;
        if (v < 0) {
            sum2 = 0;
            while ((p < pend) && ((v = *p) <= 0)) {
                sum2 += v;
                p++;
            }
            if (p >= pend) break;
            sum += sum2;
            if (sum < 0) sum = 0;
        }
    }

    if (maxSum < sum) maxSum = sum;

    if (maxSum <= 0) { //In case all nums are non-positive, return the max number
        p = nums;
        while (p < pend) {
            sum = *p++;
            if (maxSum < sum) maxSum = sum;
        }
    }

    return maxSum;
}
