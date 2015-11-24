/**

https://leetcode.com/problems/largest-rectangle-in-histogram/

Given n non-negative integers representing the histogram's bar height where the width of each bar
is 1, find the area of largest rectangle in the histogram.

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].

The largest rectangle is shown in the shaded area, which has area = 10 unit.

For example,
Given height = [2,1,5,6,2,3],
return 10.
*/
import java.lang.Math;

public class Solution {
    public static void main(String[] args) {
        Solution s = new Solution();
        System.out.format("area: %d\n", s.largestRectangleArea(new int[]{2,1,5,6,2,3}));
    }

    /**
    //This version Timeout
    public int largestRectangleArea(int[] height) {
        if ((height == null) || (height.length == 0)) return 0;
        final int N = height.length;
        int[] c = new int[N];
        int i, j, l, area, tmp;

        for (j = 0; j < N; j++) {
            c[j] = height[j];
        }

        for (l = 1; l < N; l++) {
            for (j = N - l - 1; j >= 0; j--) {
                int c1 = c[j];
                int c2 = c[j + 1];
                int h1, h2;
                h1 = height[j + l];
                h2 = height[j];
                area = Math.max(c1, c2);
                for (i = l - 1; i >= 0; i--) {
                    h1 = Math.min(h1, height[j + i]);
                    tmp = h1 * (l - i + 1);
                    if (area < tmp) area = tmp;
                }
                for (i = 1; i <= l; i++) {
                    h2 = Math.min(h2, height[j + i]);
                    tmp = h2 * (i + 1);
                    if (area < tmp) area = tmp;
                }
                c[j] = area;
            }
        }
        return c[0];
    }
    */

    //4ms version, using O(n) stack space, O(n^2) time
    public int largestRectangleArea(int[] height) {
        if ((height == null) || (height.length == 0)) return 0;
        final int N = height.length;
        int[] s = new int[N + 1];
        int i, top = 0, hi, area = 0;
        s[0] = -1;
        for (i = 0; i < N; i++) {
            hi = height[i];
            while ((top > 0) && (height[s[top]] > hi)) {
                area = Math.max(area, height[s[top]] * (i - s[top - 1] - 1));
                top--;
            }
            s[++top] = i;
        }
        while (top > 0) {
            area = Math.max(area, height[s[top]] * (N - s[top -1] - 1));
            top--;
        }
        return area;
    }
}
