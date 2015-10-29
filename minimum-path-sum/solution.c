/*
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right
which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.
*/

int minPathSum(int** grid, int gridRowSize, int gridColSize) {
    if (!grid || !gridRowSize || !gridColSize) return INT_MAX;

    const int M = gridRowSize;
    const int N = gridColSize;
    int c[M][N];
    int i, j;

    c[0][0] = grid[0][0];
    for (i = 1; i < M; i++) {
        c[i][0] = c[i - 1][0] + grid[i][0];
    }
    for (j = 1; j < N; j++) {
        c[0][j] = c[0][j - 1] + grid[0][j];
    }

    for (i = 1; i < M; i++) {
        for (j = 1; j < N; j++) {
            c[i][j] = grid[i][j] + ((c[i - 1][j] < c[i][j - 1]) ? c[i - 1][j] : c[i][j - 1]);
        }
    }
    #ifdef MY_UNIT_TEST
    printf("[");
    for (i = 1; i < M; i++) {
        printf("[");
        for (j = 1; j < N; j++) {
            printf(",%d", c[i][j]);
        }
        printf("]\n");
    }
    printf("]\n");
    #endif
    return c[M - 1][N - 1];
}
