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

int** generateMatrix(int n);

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int** ret;
    int n = atoi(argv[1]);
    gettimeofday(&tvStart, NULL);
    ret = generateMatrix(n);
    gettimeofday(&tvEnd, NULL);

    printf("generateMatrix(%d):\n\t[", atoi(argv[1]));
    for (int i = 0; i < n - 1; i++) {
        printf("[");
        for (int j = 0; j < n; j++) {
            printf(",%3d", ret[i][j]);
        }
        printf("]\n\t ");
    }
    if (n > 0) {
        printf("[");
        for (int j = 0; j < n; j++) {
            printf(",%3d", ret[n - 1][j]);
        }
        printf("]");
    }
    printf("]\n");
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, generateMatrix\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif

/*
Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

For example,
Given n = 3,

You should return the following matrix:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
*/
/**
 * Return an array of arrays.
 * Note: The returned array must be malloced, assume caller calls free().
 */
//0ms version
int** generateMatrix(int n) {
    if (!n) return NULL;
    int** ret = (int**)malloc(sizeof(int*) * n);

    if (!ret) {
        return NULL;
    }

    int lLimit, rLimit, tLimit, bLimit, i, j;

    for (i = 0; i < n; i++) {
        ret[i] = (int*)malloc(sizeof(int) * n);
        if (!ret[i]) {
            while (--i >= 0) free(ret[i]);
            free(ret);
            return NULL;
        }
    }

    lLimit = tLimit = 0;
    rLimit = bLimit = n - 1;

    int id = 1;
    while (1) {
        for (j = lLimit; j <= rLimit; j++) ret[tLimit][j] = id++;
        if (++tLimit > bLimit) break;

        for (i = tLimit; i <= bLimit; i++) ret[i][rLimit] = id++;
        if (--rLimit < lLimit) break;

        for (j = rLimit; j >= lLimit; j--) ret[bLimit][j] = id++;
        if (--bLimit < tLimit) break;

        for (i = bLimit; i >= tLimit; i--) ret[i][lLimit] = id++;
        if (++lLimit > rLimit) break;
    }
bail:
    return ret;
}
