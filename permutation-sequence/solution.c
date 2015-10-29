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

char* getPermutation(int n, int k);

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    char* ret;
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    gettimeofday(&tvStart, NULL);
    ret = getPermutation(n, k);
    gettimeofday(&tvEnd, NULL);

    printf("getPermutation(%d, %d): '%s'\n", n, k, ret);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, getPermutation\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif
/*
The set [1,2,3,…,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3):

"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.

Note: Given n will be between 1 and 9 inclusive.
*/
//0ms version
char* getPermutation(int n, int k) {
    if (((unsigned int)n) > 9) return NULL;
    int d[8] = { 0 };
    char buf[] = "1234567890";
    char* ret = strdup(buf);
    if (!ret) {
        return NULL;
    }
    buf[n] = ret[n] = '\0';

    k--;
    if (n == 1) {
        if (!k) return ret;
        free(ret);
        return NULL;
    }

    int i, j;
    for (i = 2; i <= n; i++) {
        d[n - i] = k % i;
        k = k / i;
        if (!k) break;
    }

    if (k != 0) {
        free(ret);
        return NULL;
    }

    #ifdef MY_UNIT_TEST
    printf("k %d, d[%d]:", k, n);
    for (i = 0; i < n - 1; i++) printf(",%d", d[i]);
    printf("\n");
    #endif

    for (i = 0; i < n - 1; i++) {
        for (j = d[i], k = 0; j >= 0; k++) {
            if (buf[k] != 0) {
                j--;
            }
        }
        k--;
        ret[i] = buf[k];
        buf[k] = '\0';
    }
    for (k = 0; k < n; k++) {
        if (buf[k] != 0) {
            ret[n - 1] = buf[k];
        }
    }
    return ret;
}
