/**
Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing all ones
and return its area.
*/
public class Solution {
    private int getMax(int[] c, int[] s) {
        final int N = c.length;
        int i, top = 0, max = 0;
        for (i = 0; i < N; i++) {
            while ((top > 0) && (c[s[top]] >= c[i])) {
                max = Math.max(max, c[s[top]] * (i - s[top - 1] - 1));
                top--;
            }
            s[++top] = i;
        }
        while (top > 0) {
            max = Math.max(max, c[s[top]] * (N - s[top - 1] - 1));
            top--;
        }
        return max;
    }

    //7ms, O(mn)
    public int maximalRectangle(char[][] matrix) {
        if (matrix == null) return 0;
        final int M = matrix.length;
        if (M <= 0) return 0;
        final int N = matrix[0].length;
        if (N <= 0) return 0;
        int i, j, area = 0;
        int c[] = new int[N];
        int s[] = new int[N + 1];
        s[0] = -1;
        for (i = 0; i < M; i++) {
            for (j = 0; j < N; j++) {
                if (matrix[i][j] == '1') {
                    c[j] += 1;
                } else {
                    c[j] = 0;
                }
            }
            area = Math.max(area, getMax(c, s));
        }
        return area;
    }
}
