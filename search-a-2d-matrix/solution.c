/*
Write an efficient algorithm that searches for a value in an m x n matrix.
This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.
For example,

Consider the following matrix:

[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
Given target = 3, return true.
*/
//4ms, O(logN) time, O(1) space
bool searchMatrix(int** matrix, int matrixRowSize, int matrixColSize, int target) {
    if (!matrix || (matrixRowSize <= 0) || (matrixColSize <= 0)) return false;

    int low, high, mid, row;

    for (low = 0, high = matrixRowSize - 1; low <= high;) {
        mid = (low + high + 1) >> 1;
        if (matrix[mid][0] < target) {
            low = mid + 1;
        } else if (matrix[mid][0] > target) {
            high = mid - 1;
        } else {
            return true;
        }
    }
    row = high;
    if (row < 0) return false;
    for (low = 0, high = matrixColSize - 1; low <= high;) {
        mid = (low + high + 1) >> 1;
        if (matrix[row][mid] < target) {
            low = mid + 1;
        } else if (matrix[row][mid] > target) {
            high = mid - 1;
        } else {
            return true;
        }
    }
    return false;
}
