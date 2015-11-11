/*
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
*/
import java.util.*;

public class Solution {
    /*
    private void mysub(List<List<Integer>>ll, List<Integer> l, int[] nums, int k) {
        if (k < 0) {
            return;
        } else if (k == 0) {
            ll.add(new ArrayList<Integer>(l));
            if (D) System.out.format("Collected list %s\n", ll.toString());
        } else {
            for (int i = 0; i < nums.length; i++) {
                if (nums[i] > 0) {
                    int t = nums[i];
                    nums[i] = 0;
                    l.add(new Integer(t));
                    mysub(ll, l, nums, k - 1);
                    if (D) System.out.format("Checked nums[%d] - %d, k - 1 = %d, l %s\n", i, nums[i], k - 1, l);
                    l.remove(l.size() - 1);
                    nums[i] = t;
                }
            }
        }
    }

    //Timeout
    public List<List<Integer>> combine(int n, int k) {
        List<Integer> l = new ArrayList<Integer>();
        List<List<Integer>> ret = new ArrayList<List<Integer>>();
        int[] nums = new int[n];
        for (int i = 0; i < n; i++) nums[i] = (i + 1);
        mysub(ret, l, nums, k);
        return ret;
    }*/

    private void mysub(List<List<Integer>>ll, List<Integer> l, int start, int n, int k) {
        if (k < 0) {
            return;
        } else if (k == 0) {
            ll.add(new ArrayList<Integer>(l));
            if (D) System.out.format("Collected list %s\n", ll.toString());
        } else {
            for (int i = start; i <= n; i++) {
                l.add(i);
                mysub(ll, l, i + 1, n, k - 1);
                l.remove(l.size() - 1);
                if (D) System.out.format("Checked num %d, k - 1 = %d, l %s\n", i, k - 1, l);
            }
        }
    }

    //3ms
    public List<List<Integer>> combine(int n, int k) {
        List<Integer> l = new ArrayList<Integer>();
        List<Integer> r = new ArrayList<Integer>();
        List<List<Integer>> ret = new ArrayList<List<Integer>>();
        mysub(ret, l, 1, n, k);
        return ret;
    }

    private static final boolean D = false;
    public static void main(String[] args) {
    }
}
