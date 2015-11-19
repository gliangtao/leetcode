/*
Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3.
It doesn't matter what you leave beyond the new length.
*/

import java.lang.System;

public class Solution {
    //2ms version
    public int removeDuplicates(int[] nums) {
        int N;
        if ((nums == null) || ((N = nums.length) == 0)) {
            return 0;
        }
        int ret = N;
        int val = nums[0];
        int i = 1;
        while (true) {
            int repeat = -1;
            while ((i < ret) && (nums[i] == val)) {
                repeat++;
                i++;
            }
            if (repeat > 0) {
                System.arraycopy(nums, i, nums, i - repeat, ret - i);
                ret -= repeat;
                i -= repeat;
            }
            if (i >= ret) break;
            val = nums[i++];
        }
        return ret;
    }
}
