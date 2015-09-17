public class Solution {
    public int[] twoSum(int[] nums, int target) {
        int max = 0;
        int t;
        for (int i = 0; i < nums.length; i++) {
            nums[i] = t = (nums[i] << 1) - target;
            if (t < 0 ) {
                t = -t;
            }
            if (max < t) {
                max = t;
            }
        }
        int[] ht = new int[max + 1];
        for (int i = 0; i <= max; i++) {
            ht[i] = -1;
        }
        for (int i = 0; i < nums.length; i++) {
            t = nums[i];
            if (t < 0) {
                t = -t;
            }
            if (ht[t] >= 0) {
                if (nums[ht[t]] + nums[i] == 0) {
                    int[] ret = new int[2];
                    ret[0] = ht[t] + 1;
                    ret[1] = i + 1;
                    return ret;
                }
            }
            ht[t] = i;
        }
        return null;
    }
}
