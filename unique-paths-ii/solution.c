/*
Follow up for "Unique Paths":

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

For example,
There is one obstacle in the middle of a 3x3 grid as illustrated below.

[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
The total number of unique paths is 2.

Note: m and n will be at most 100.
*/
//0ms version, O(mxn) time & space
int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridRowSize, int obstacleGridColSize) {
    if (!obstacleGrid || (obstacleGridRowSize <= 0) || (obstacleGridColSize <= 0)) return 0;

    int i, j;

    const int M = obstacleGridRowSize;
    const int N = obstacleGridColSize;
    int** o = obstacleGrid;

    if (o[0][0] || o[M-1][N-1]) return 0;

    int c[M][N];

    for (i = 0; i < M; i++) {
        if (o[i][0]) {
            for (;i < M; i++) c[i][0] = 0;
            break;
        }
        c[i][0] = 1;
    }
    for (j = 0; j < N; j++) {
        if (o[0][j]) {
            for (; j < N; j++) c[0][j] = 0;
            break;
        }
        c[0][j] = 1;
    }

    for (i = 1; i < M; i++) {
        for (j = 1; j < N; j++) {
            if (o[i][j]) {
                c[i][j] = 0;
            } else {
                c[i][j] = c[i - 1][j] + c[i][j - 1];
            }
        }
    }
    return c[M - 1][N - 1];
}
