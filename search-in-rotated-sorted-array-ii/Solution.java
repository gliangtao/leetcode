/*
Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?

Write a function to determine if a given target is in the array.
*/
public class Solution {
    //1-2 ms version
    public boolean search(int[] nums, int target) {
        if (nums == null) return false;
        int N = nums.length - 1;
        if (N < 0) return false;
        int n0 = nums[0];
        if (target == n0) return true;
        int l, r, m, i, d;
        if (n0 < nums[N]) {
            l = 1;
            r = N;
        } else {
            r = N;
            while ((r > 0) && (nums[r] == n0)) r--;
            N = r;
            for (l = 1; l <= r;) {
                i = (l + r) >> 1;
                if (nums[i] >= n0) {
                    l = i + 1;
                } else {
                    r = i - 1;
                }
            }
            if (target < n0) {
                l = r;
                r = N;
            } else {
                l = 1;
            }
        }
        while (l <= r) {
            i = (l + r + 1) >> 1;
            d = nums[i] - target;
            if (d < 0) {
                l = i + 1;
            } else if (d > 0) {
                r = i - 1;
            } else {
                return true;
            }
        }
        return false;
    }
}
