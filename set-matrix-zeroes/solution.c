
/*
Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.

Follow up:
Did you use extra space?
A straight forward solution using O(mn) space is probably a bad idea.
A simple improvement uses O(m + n) space, but still not the best solution.
Could you devise a constant space solution?
*/
#if 0
//40ms, Time O(m*n), space O(n)
void setZeroes(int** matrix, int matrixRowSize, int matrixColSize) {
    if (!matrix || (matrixRowSize <= 0) || (matrixColSize<= 0)) return;
    const int NCOLS = matrixColSize;
    int zeroCols[NCOLS];
    int i, j, m, n, zero_row;
    memset(zeroCols, 0, sizeof(int) * NCOLS);
    for (i = 0; i < matrixRowSize; i++) {
        zero_row = 0;
        for (j = 0; j < NCOLS; j++) {
            if (matrix[i][j] == 0) {
                zeroCols[j] = 1;
                zero_row = 1;
            }
        }
        if (zero_row) {
            for (n = 0; n < NCOLS; n++) if (matrix[i][n]) matrix[i][n] = 0;
        }
    }
    for (j = 0; j < NCOLS; j++) {
        if (zeroCols[j]) {
            for (m = 0; m < matrixRowSize; m++) if (matrix[m][j]) matrix[m][j] = 0;
        }
    }
}
#endif

#if 0
//44ms, Time O(m*n), space O(1)
void setZeroes(int** matrix, int matrixRowSize, int matrixColSize) {
    if (!matrix || (matrixRowSize <= 0) || (matrixColSize<= 0)) return;
    const int NCOLS = matrixColSize;
    int i, j, m, n, last_zero_row = matrixRowSize, cur_zero_row = matrixRowSize, row_0_zero = 0;
    for (i = 0; i < matrixRowSize; i++) {
        cur_zero_row = matrixRowSize;
        for (j = 0; j < NCOLS; j++) {
            if (matrix[i][j] == 0) {
                matrix[0][j] = 0;
                cur_zero_row = i;
            }
        }
        if (last_zero_row < matrixRowSize) {
            if (last_zero_row == 0) {
                row_0_zero = 1;
            } else {
                for (n = 0; n < NCOLS; n++) {
                    if (matrix[last_zero_row][n]) matrix[last_zero_row][n] = 0;
                }
            }
        }
        last_zero_row = cur_zero_row;
    }
    for (j = 0; j < NCOLS; j++) {
        if (matrix[0][j] == 0) {
            for (m = 1; m < matrixRowSize; m++) if (matrix[m][j]) matrix[m][j] = 0;
        }
    }
    if (last_zero_row < matrixRowSize) {
        for (n = 0; n < NCOLS; n++) if (matrix[last_zero_row][n]) matrix[last_zero_row][n] = 0;
    }
    if (row_0_zero) {
        for (n = 0; n < NCOLS; n++) if (matrix[0][n]) matrix[0][n] = 0;
    }
}

#endif

//44ms, O(1) space, O(m*n) time
void setZeroes(int** matrix, int matrixRowSize, int matrixColSize) {
    if (!matrix || (matrixRowSize <= 0) || (matrixColSize<= 0)) return;
    const int NCOLS = matrixColSize;
    int i, j, m, n, row_0_zero = 0, row_zero;
    for (i = 0; i < matrixRowSize; i++) {
        row_zero = 0;
        for (j = 0; j < NCOLS; j++) {
            if (matrix[i][j] == 0) {
                matrix[0][j] = 0;
                if (i == 0) {
                    if (!row_0_zero) row_0_zero = 1;
                } else {
                    if (!row_zero) row_zero = 1;
                }
            }
        }
        if (row_zero) {
            for (n = 0; n < NCOLS; n++) if (matrix[i][n]) matrix[i][n] = 0;
        }
    }
    for (j = 0; j < NCOLS; j++) {
        if (matrix[0][j] == 0) {
            for (m = 1; m < matrixRowSize; m++) if (matrix[m][j]) matrix[m][j] = 0;
        }
    }
    if (row_0_zero) {
        for (n = 0; n < NCOLS; n++) if (matrix[0][n]) matrix[0][n] = 0;
    }
}
