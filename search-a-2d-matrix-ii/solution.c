/*
Write an efficient algorithm that searches for a value in an m x n matrix.
This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.
For example,

Consider the following matrix:

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
Given target = 5, return true.

Given target = 20, return false.
*/

#if 0
//168ms, O(nlgN)
bool searchMatrix(int** matrix, int matrixRowSize, int matrixColSize, int target) {
    if (!matrix || (matrixRowSize <= 0) || (matrixColSize <= 0)) return false;

    int low, high, mid, row, mid_row;

    for (low = 0, high = matrixRowSize - 1; low <= high;) {
        mid = (low + high + 1) >> 1;
        if (matrix[mid][0] > target) {
            high = mid - 1;
        } else if (matrix[mid][matrixColSize - 1] < target) {
            low = mid + 1;
        } else {
            if ((matrix[mid][0] == target) || (matrix[mid][matrixColSize - 1] == target)) {
                return true;
            }
            break;
        }
    }
    mid_row = mid;
    for (row = mid_row; row >= 0; row--) {
        if (matrix[row][matrixColSize - 1] < target) break;
        if (matrix[row][matrixColSize - 1] == target) return true;
        for (low = 0, high = matrixColSize - 1; low <= high;) {
            mid = (low + high + 1) >> 1;
            if (matrix[row][mid] > target) {
                high = mid - 1;
            } else if (matrix[row][mid] < target) {
                low = mid + 1;
            } else {
                return true;
            }
        }
    }
    for (row = mid_row + 1; row < matrixRowSize; row++) {
        if (matrix[row][0] > target) break;
        if (matrix[row][0] == target) return true;
        for (low = 0, high = matrixColSize - 1; low <= high;) {
            mid = (low + high + 1) >> 1;
            if (matrix[row][mid] > target) {
                high = mid - 1;
            } else if (matrix[row][mid] < target) {
                low = mid + 1;
            } else {
                return true;
            }
        }
    }
    return false;
}
#endif

//100ms, O(m+n)
bool searchMatrix(int** matrix, int matrixRowSize, int matrixColSize, int target) {
    if (matrix && (matrixRowSize > 0) && (matrixColSize > 0)) {
        register int x, y;
        for (x = 0, y = matrixRowSize - 1;;) {
            register int d = matrix[y][x] - target;
            if (d < 0) {
                if (++x >= matrixColSize) break;
            } else if (d == 0) {
                return true;
            } else {
                if (--y < 0) break;
            }
        }
    }
    return false;
}
