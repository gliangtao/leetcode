/*
Given a set of distinct integers, nums, return all possible subsets.

Note:
Elements in a subset must be in non-descending order.
The solution set must not contain duplicate subsets.
For example,
If nums = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
*/

public class Solution {
    private void mysub(List<List<Integer>> ll, List<Integer> l, int[] nums, int start) {
        if (start == nums.length) {
            return;
        }
        for (int i = start; i < nums.length; i++) {
            l.add(nums[i]);
            ll.add(new ArrayList<Integer>(l));
            mysub(ll, l, nums, i + 1);
            l.remove(l.size() - 1);
        }
    }
    //3ms Accepted
    public List<List<Integer>> subsets(int[] nums) {
        if (nums == null) return null;
        Arrays.sort(nums);
        List<List<Integer>> ret = new ArrayList<List<Integer>>();
        List<Integer> l = new ArrayList<Integer>();
        ret.add(new ArrayList<Integer>());
        mysub(ret, l, nums, 0);
        return ret;
    }
    public static void main(String[] args) {
    }
}
