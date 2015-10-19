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

//int NUMS[] = { 1000, -1 };
//int NUMS[] = { 0 };
int NUMS[] = { 1, 0 };

int firstMissingPositive(int* nums, int numsSize);

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int i;
    gettimeofday(&tvStart, NULL);
    i = firstMissingPositive(NUMS, sizeof(NUMS) / sizeof(NUMS[0]));
    gettimeofday(&tvEnd, NULL);
    
    printf("First missing positive: %d, array:\n", i);
    for (int i = 0; i < sizeof(NUMS) / sizeof(NUMS[0]); i++) {
        printf(",%d", NUMS[i]);
    }
    printf("\n");
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    DBG("Time %d.%06d, firstMissingPositive\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif

/*
Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space.
*/
#include <limits.h>

int firstMissingPositive(int* nums, int numsSize) {
    if (!nums || !numsSize) {
        return 1;
    }

    int i, r, t, min, cap;
    for (i = 0, min = INT_MAX, r = numsSize - 1; i <= r; i++) {
        t = nums[i];
        if (t <= 0) {
            while ((nums[r] <= 0) && (r >= i)) r--; //r - new head of non-positive integers rightside
            if (r < i) {
                if (r < 0) return 1;
                break;
            }
            nums[i] = nums[r];
            nums[r] = t;
            t = nums[i];
            r--;
        }
        if (min > t) min = t;
    }

    if (min != 1) return 1; //For this specific problem, if min != 1 then 1 is always the answer

    numsSize = i;
    cap = i + min - 1;
    for (i = 0, r = numsSize - 1, t = nums[0]; i <= r; t = nums[i]) {
        if (t == min + i) {
            i++;
            if (r < i) break;
            continue;
        }

        if ((t <= cap) && (nums[t - min] != t)) {
            nums[i] = nums[t - min];
            nums[t - min] = t;
            continue;
        }

        while ((r >= i) && (nums[r] > cap)) {
            r--;
            cap--;
        }
        if (r < i) break;
        nums[i] = nums[r];
        nums[r] = t;
        r--;
        cap--;
    }

    for (i = 0; i <= r; i++) {
        if (nums[i] != min + i) break;
    }
    return (min + i);
}
