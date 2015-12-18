
//0ms, O(n^3), row-by-row scanning
int numIslands(char** grid, int gridRowSize, int gridColSize) {
    const int N = gridColSize;
    int is[N];
    int i, j, k, id = 0, dup = 0;
    memset(is, 0, N * sizeof(int));
    for (i = 0; i < gridRowSize; i++) {
        for (j = 0; j < gridColSize; j++) {
            if ((i == 0) || (grid[i][j] != grid[i - 1][j])) {
                if (grid[i][j] == '1') {
                    if ((j > 0) && (grid[i][j - 1] == '1')) {
                        is[j] = is[j - 1];
                    } else {
                        is[j] = ++id;
                    }
                } else {
                    is[j] = 0;
                }
            } else if (grid[i][j] == '1') {
                if ((j > 0) && (grid[i][j - 1] == '1')) {
                    if (is[j] == is[j - 1]) {
                    } else if (is[j] == 0) {
                        is[j] = is[j - 1];
                    } else {
                        dup++;
                        for (k = 0; k < N; k++) if (is[k] == is[j - 1]) is[k] = is[j];
                    }
                }
            }
        }
    }
    return (id - dup);
}
