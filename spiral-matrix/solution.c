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


int* spiralOrder(int** matrix, int matrixRowSize, int matrixColSize);

//static int M[3][3] = { {1,2,3}, {4,5,6}, {7,8,9} };
//static int M[1][10] = {{1,2,3,4,5,6,7,8,9,10}};
static int M[1][1] = {{1}};
int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int retSize;
    const int* MP[sizeof(M) / sizeof(M[0])];
    for (int i = 0; i < sizeof(M) / sizeof(M[0]); i++) MP[i] = M[i];
    gettimeofday(&tvStart, NULL);
    spiralOrder((int**)MP, sizeof(M) / sizeof(M[0]), sizeof(M[0]) / sizeof(M[0][0]));
    gettimeofday(&tvEnd, NULL);
    
    //printf("spiralOrder: %d\n", retSize);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, spiralOrder\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif

/*
Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

For example,
Given the following matrix:

[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
You should return [1,2,3,6,9,8,7,4,5].
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
//0ms version
int* spiralOrder(int** matrix, int matrixRowSize, int matrixColSize) {
    if (!matrix || !matrixRowSize || !matrixColSize) return NULL;

    int* ret = (int*)malloc(sizeof(int) * matrixRowSize * matrixColSize);
    if (!ret) return NULL;

    int lLimit, rLimit, tLimit, bLimit;

    lLimit = tLimit = 0;
    rLimit = matrixColSize - 1;
    bLimit = matrixRowSize - 1;

    int* p;
    int i, j;

    DBG("ret:");
    p = ret;
    while (1) {
        for (j = lLimit; j <= rLimit; j++) {
            *p++ = matrix[tLimit][j];
            DBG(",%d", p[-1]);
        }
        if (++tLimit > bLimit) break;
        for (i = tLimit; i <= bLimit; i++) {
            *p++ = matrix[i][rLimit];
            DBG(",%d", p[-1]);
        }
        if (--rLimit < lLimit) break;
        for (j = rLimit; j >= lLimit; j--) {
            *p++ = matrix[bLimit][j];
            DBG(",%d", p[-1]);
        }
        if (--bLimit < tLimit) break;
        for (i = bLimit; i >= tLimit; i--) {
            *p++ = matrix[i][lLimit];
            DBG(",%d", p[-1]);
        }
        if (++lLimit > rLimit) break;
    }
    DBG("\n");

    return ret;
}
