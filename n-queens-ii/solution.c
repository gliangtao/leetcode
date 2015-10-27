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

int totalNQueens(int n);

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int retSize;
    gettimeofday(&tvStart, NULL);
    retSize = totalNQueens(atoi(argv[1]));
    gettimeofday(&tvEnd, NULL);
    
    printf("totalNQueens: %d\n", retSize);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, totalNQueens\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif

/*
Follow up for N-Queens problem.

Now, instead outputting board configurations, return the total number of distinct solutions.
*/

static int mySub(int* c, int k, int n) {
    int ret, i, j, vi;
    int vk = c[k];
    if (k == n - 1) {
        for (j = 0; j < k; j++) {
            int d = vk - c[j];
            if ((k - j == d) || (j - k == d)) return 0;
        }
        return 1;
    }

    ret = 0;

    for (j = 0; j < k; j++) {
        int d = vk - c[j];
        if ((k - j == d) || (j - k == d)) break;
    }
    if (j >= k) ret += mySub(c, k + 1, n);

    for (i = k + 1; i < n; i++) {
        vi = c[i];
        c[i] = vk;
        c[k] = vi;

        for (j = 0; j < k; j++) {
            int d = vi - c[j];
            if ((k - j == d) || (j - k == d)) break;
        }
        if (j >= k) ret += mySub(c, k + 1, n);

        c[i] = vi;
        c[k] = vk;
    }
    return ret;
}

//0ms version
int totalNQueens(int n) {
    int retSize = 0;
    int* c = NULL;
    if (n <= 0) goto bail;

    int i;

    c = (int*)malloc(n * sizeof(int));
    if (!c) goto bail;
    for (i = 0; i < n; i++) {
        c[i] = i;
    }

    //c[], k, n
    retSize = mySub(c, 0, n);

bail:
    free(c);
    return retSize;
}
