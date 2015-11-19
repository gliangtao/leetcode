/*
Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are
those horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example,
Given board =

[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]
word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
*/

public class Solution {
    private boolean mysub(char[][] board, String word, int M, int N, int i, int j, int k) {
        if (k < 0) return true;
        char ch = word.charAt(k);
        //Note: The order of the following checks matters - esp for all-equal chars!
        if ((j > 0) && (board[i][j - 1] == ch)) {
            board[i][j - 1] = 0;
            if (mysub(board, word, M, N, i, j - 1, k - 1)) return true;
            board[i][j - 1] = ch;
        }
        if ((i > 0) && (board[i - 1][j] == ch)) {
            board[i - 1][j] = 0;
            if (mysub(board, word, M, N, i - 1, j, k - 1)) return true;
            board[i - 1][j] = ch;
        }
        if ((j < N) && (board[i][j + 1] == ch)) {
            board[i][j + 1] = 0;
            if (mysub(board, word, M, N, i, j + 1, k - 1)) return true;
            board[i][j + 1] = ch;
        }
        if ((i < M) && (board[i + 1][j] == ch)) {
            board[i + 1][j] = 0;
            if (mysub(board, word, M, N, i + 1, j, k - 1)) return true;
            board[i + 1][j] = ch;
        }
        return false;
    }

    //9ms version
    public boolean exist(char[][] board, String word) {
        if ((board == null) || (word == null)) return false;
        final int M = board.length - 1;
        final int N = board[0].length - 1;

        int lastw = word.length() - 1;
        if (lastw < 0) return true;
        for (int i = M; i >= 0; i--) {
            for (int j = N; j >= 0; j--) {
                if (board[i][j] == word.charAt(lastw)) {
                    board[i][j] = 0;
                    if (mysub(board, word, M, N, i, j, lastw - 1)) return true;
                    board[i][j] = word.charAt(lastw);
                }
            }
        }
        return false;
    }
}
