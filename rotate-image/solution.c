
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

//int M[4][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
int M[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
void rotate(int** matrix, int matrixRowSize, int matrixColSize);

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int retSize;
    const int n = sizeof(M) / sizeof(M[0]);
    int* m[n];
    for (int i = 0; i < n; i++) {
        m[i] = M[i];
    }
    printf("Before Rotate:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf(",%02d",M[i][j]);
        printf("\n");
    }
    gettimeofday(&tvStart, NULL);
    rotate(m, n, n);
    gettimeofday(&tvEnd, NULL);

    printf("After Rotate:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf(",%02d",M[i][j]);
        printf("\n");
    }
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    DBG("Time %d.%06d, rotate\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif

/*
You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Follow up:
Could you do this in-place?
*/
//0ms version
void rotate(int** matrix, int matrixRowSize, int matrixColSize) {
    if (!matrix || !matrixRowSize || (matrixRowSize != matrixColSize)) {
        return;
    }

    const int L2 = matrixRowSize - 1;
    const int LX = L2 >> 1;
    const int LY = LX - (matrixRowSize & 1);
    int** m = matrix;
    int i, j;
    //m[i,j] -> m[j,L2-i] -> m[L2-i, L2-j] -> m[L2-j, i] -> m[i,j];
    int v1, v2, v3, v4;
    for (i = 0; i <= LX; i++) {
        for (j = 0; j <= LY; j++) {
            v1 = m[i][j];
            v2 = m[j][L2-i];
            v3 = m[L2-i][L2-j];
            v4 = m[L2-j][i];
            m[j][L2-i]      = v1;
            m[L2-i][L2-j]   = v2;
            m[L2-j][i]      = v3;
            m[i][j]         = v4;
        }
    }
}
