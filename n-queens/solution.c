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

char*** solveNQueens(int n, int* returnSize);

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int retSize;
    gettimeofday(&tvStart, NULL);
    solveNQueens(atoi(argv[1]), &retSize);
    gettimeofday(&tvEnd, NULL);
    
    printf("solveNQueens: %d\n", retSize);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, solveNQueens\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif

/*
The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens
attack each other.



Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.'
both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
*/

typedef struct MyPuzzle {
    struct MyPuzzle*    next;
    int                 c[0];
} MyPuzzle;

static int mySub(int* c, int k, int n, MyPuzzle** head) {
    int ret, i, j, vi;
    int vk = c[k];
    if (k == n - 1) {
        for (j = 0; j < k; j++) {
            int d = vk - c[j];
            if ((k - j == d) || (j - k == d)) return 0;
        }
        MyPuzzle* puzzle = (MyPuzzle*)malloc(sizeof(MyPuzzle) + (sizeof(int) * n));
        if (!puzzle) return 0;
        puzzle->next = *head;
        memcpy(puzzle->c, c, sizeof(int) * n);
        *head = puzzle;
        return 1;
    }

    ret = 0;

    for (j = 0; j < k; j++) {
        int d = vk - c[j];
        if ((k - j == d) || (j - k == d)) break;
    }
    if (j >= k) ret += mySub(c, k + 1, n, head);

    for (i = k + 1; i < n; i++) {
        vi = c[i];
        c[i] = vk;
        c[k] = vi;

        for (j = 0; j < k; j++) {
            int d = vi - c[j];
            if ((k - j == d) || (j - k == d)) break;
        }
        if (j >= k) ret += mySub(c, k + 1, n, head);

        c[i] = vi;
        c[k] = vk;
    }
    return ret;
}

/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
//4ms version
char*** solveNQueens(int n, int* returnSize) {
    char*** ret = NULL;
    int retSize = 0;
    MyPuzzle* head = NULL;
    char* oneRow = NULL;
    char** bufs = NULL;
    int* c = NULL;
    if (n <= 0) goto bail;

    oneRow = (char*)malloc(sizeof(char) * (n + 1));
    bufs = (char**)malloc(sizeof(char*) * n);
    if (!bufs) goto bail;

    int i, j, k;
    memset(oneRow, '.', n * sizeof(char));
    oneRow[n] = '\0';
    memset(bufs, 0, sizeof(char*) * n);
    for (i = 0; i < n; i++) {
        if (NULL == (bufs[i] = strdup(oneRow))) goto bail;
        bufs[i][i] = 'Q';
    }

    c = (int*)malloc(n * sizeof(int));
    if (!c) goto bail;
    for (i = 0; i < n; i++) {
        c[i] = i;
    }

    //c[], k, n, &head
    retSize = mySub(c, 0, n, &head);
    ret = (char***)malloc(sizeof(char**) * retSize);
    if (!ret) goto bail;

    MyPuzzle* next;
    char*** pRet = ret;
    while (head != NULL) {
        char** sa = (char**)malloc(sizeof(char*) * n);
        if (!sa) {
            retSize = (int)(pRet - ret);
            goto bail;
        }
        next = head->next;
        DBG("ret[%d]:", (int)(pRet - ret));
        for (i = 0; i < n; i++) {
            if (NULL == (sa[i] = strdup(bufs[head->c[i]]))) {
                retSize = (int)(pRet - ret);
                free(sa);
                goto bail;
            }
            #ifdef MY_UNIT_TEST
            if (!i) {
                DBG("\n\t[\"%s\"", sa[i]);
            } else {
                DBG("\n\t \"%s\"", sa[i]);
            }
            #endif
        }
        DBG("]\n");
        *pRet++ = sa;
        free(head);
        head = next;
    }

bail:
    if (returnSize) *returnSize = retSize;
    free(oneRow);
    if (bufs) {
        for (i = 0; i < n; i++) {
            free(bufs[i]);
        }
        free(bufs);
    }
    free(c);
    return ret;
}
