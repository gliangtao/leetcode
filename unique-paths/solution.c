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

int uniquePaths(int m, int n);

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int ret;
    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    gettimeofday(&tvStart, NULL);
    ret = uniquePaths(m, n);
    gettimeofday(&tvEnd, NULL);

    printf("uniquePaths(%d, %d): %d\n", m, n, ret);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, uniquePaths\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif

/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach
the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?


Above is a 3 x 7 grid. How many possible unique paths are there?

Note: m and n will be at most 100.
*/
//0ms, DP, O(n^2)
int uniquePaths(int m, int n) {
    if ((m <= 0) || (n <= 0)) return 0;
    if ((m == 1) || (n == 1)) return 1;

    int i, j;
    const int M = m;
    const int N = n;
    int c[M][N];
    for (i = 0; i < M; i++) c[i][0] = 1;
    for (j = 1; j < N; j++) c[0][j] = 1;
    for (i = 1; i < M; i++) {
        for (j = 1; j < N; j++) {
            c[i][j] = c[i - 1][j] + c[i][j - 1];
        }
    }
    return c[M - 1][N - 1];
}
