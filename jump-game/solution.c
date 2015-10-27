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


bool canJump(int* nums, int numsSize);
static int N[] =
{3,2,1,0,4};
//{3,2,1,4};

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    bool retVal;
    gettimeofday(&tvStart, NULL);
    retVal = canJump(N, sizeof(N) / sizeof(N[0]));
    gettimeofday(&tvEnd, NULL);
    
    printf("canJump: %d\n", retVal);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, canJump\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif

/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false.
*/
//4ms version
bool canJump(int* nums, int numsSize) {
    if (!nums || !numsSize) return false;

    int i, range, maxRange;

    for (i = 0, maxRange = 0; i < numsSize; i++) {
        range = i + nums[i];
        if (maxRange < range) {
            if (maxRange < i) return false;
            maxRange = range;
        }
    }
    return true;
}

