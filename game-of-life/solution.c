/**
According to the Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular
automaton devised by the British mathematician John Horton Conway in 1970."

Given a board with m by n cells, each cell has an initial state live (1) or dead (0). Each cell
interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules
(taken from the above Wikipedia article):

Any live cell with fewer than two live neighbors dies, as if caused by under-population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by over-population..
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
Write a function to compute the next state (after one update) of the board given its current state.

Follow up:
Could you solve it in-place? Remember that the board needs to be updated at the same time: You
cannot update some cells first and then use their updated values to update other cells.
In this question, we represent the board using a 2D array. In principle, the board is infinite,
which would cause problems when the active area encroaches the border of the array. How would you
address these problems?
*/
#define MIN(a, b) ((a) <  (b) ? (a) : (b))
#define MAX(a, b) ((a) >= (b) ? (a) : (b))
//0ms O(1) space, O(mn) time
void gameOfLife(int** board, int boardRowSize, int boardColSize) {
    if (!board || (boardRowSize <= 0) || (boardColSize <= 0)) return;
    register int i, j, m, n;
    for (i = 0; i < boardRowSize; i++) {
        for (j = 0; j < boardColSize; j++) {
            register int t = 0;
            for (m = MAX(i - 1, 0); m < MIN(boardRowSize, i + 2); m++) {
                for (n = MAX(j - 1, 0); n < MIN(boardColSize, j + 2); n++) {
                    t += board[m][n] & 1;
                }
            }
            if ((t == 3) || ((t == 4) & board[i][j])) board[i][j] |= 2;
        }
    }
    for (i = 0; i < boardRowSize; i++) {
        for (j = 0; j < boardColSize; j++) {
            board[i][j] >>= 1;
        }
    }
}
