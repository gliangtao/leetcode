/**
Given an array nums, there is a sliding window of size k which is moving from the very left of the
array to the very right. You can only see the k numbers in the window. Each time the sliding window
moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Therefore, return the max sliding window as [3,3,5,5,6,7].

Note: 
You may assume k is always valid, ie: 1 ≤ k ≤ input array's size for non-empty array.

Follow up:
Could you solve it in linear time?
*/
public class Solution {


    private static int h2npos(int[] heap, int base, int npos, int k, int hi) {
        int i = base + heap[hi];
        if (i > npos) i -= k;
        return i;
    }

    private void moveHeap(int[] heap, int i, int[] nums, int npos, int[] n2hi) {
        int k = heap.length;
        int nval = nums[npos];
        int l, r, next, nextv, rv, base;
        base = npos - (npos % k);
        if (nval < nums[npos - k]) {
            while (i < k) {
                l = (i << 1) + 1;
                r = l + 1;
                if (l >= k) break;
                nextv = nums[h2npos(heap, base, npos, k, l)];
                next = l;
                if (r < k) {
                    rv = nums[h2npos(heap, base, npos, k, r)];
                    if (nextv < rv) {
                        next = r;
                        nextv = rv;
                    }
                }
                if (nval < nextv) {
                    n2hi[heap[i] = heap[next]] = i;
                    i = next;
                } else {
                    break;
                }
            }
        } else if (nval > nums[npos - k]) {
            while (i > 0) {
                next = (i - 1) >> 1;
                if (nval > nums[h2npos(heap, base, npos, k, next)]) {
                    n2hi[heap[i] = heap[next]] = i;
                    i = next;
                } else {
                    break;
                }
            }
        } else {
            return;
        }
        n2hi[heap[i] = (npos % k)] = i;
    }

    private void heapify(int[] heap, int i, int[] nums, int[] n2hi) {
        int k = heap.length;
        int l, r, next, t;
        while (i < k) {
            l = (i << 1) + 1;
            r = l + 1;
            if (l >= k) break;
            if (r >= k) {
                next = l;
            } else {
                next = (nums[heap[l]] < nums[heap[r]]) ? r : l;
            }
            if (nums[heap[i]] < nums[heap[next]]) {
                t = heap[i];
                n2hi[heap[i] = heap[next]] = i;
                n2hi[heap[next] = t] = next;
                i = next;
            } else {
                break;
            }
        }
    }

    //11-13ms solution, O(NlogK)
    public int[] maxSlidingWindow(int[] nums, int k) {
        int i, j, N = nums.length;
        if ((N <= 0) || (k == 0) || (k > N)) return new int[0];
        int[] heap = new int[k];
        int[] n2hi = new int[k];
        int[] ret = new int[N - k + 1];
        for (j = k - 1; j >= 0; j--) heap[j] = n2hi[j] = j;
        for (i = (k - 2) >> 1; i >= 0; i--) heapify(heap, i, nums, n2hi);
        if (D) {
            printHeap(heap, nums);
        }
        i = 0;
        ret[i++] = nums[heap[0]];
        for (j = k; j < N; j++) {
            moveHeap(heap, n2hi[j % k], nums, j, n2hi);
            if (D) {
                printHeap(heap, nums, j);
            }
            ret[i++] = nums[h2npos(heap, j - (j % k), j, k, 0)];
        }
        return ret;
    }

    private static void printHeap(int[] heap, int nums[]) {
        int hi, k = heap.length;
        System.out.format("Heap %3d:", 0);
        for (hi = 0; hi < k; hi++) {
            System.out.format(",%3d", nums[heap[hi]]);
        }
        System.out.println("");
    }
    private static void printHeap(int[] heap, int nums[], int j) {
        int hi, k = heap.length;
        System.out.format("Heap %3d:", j - k + 1);
        for (hi = 0; hi < k; hi++) {
            System.out.format(",%3d", nums[h2npos(heap, j - (j % k), j, k, hi)]);
        }
        System.out.println("");
    }

    private static final boolean D = true;
    private static final int[] N = { 1,3,1,2,0,5 };
    private static final int K = 3;
    public static void main(String[] args) {
        Solution s = new Solution();
        System.out.print("Nums:    ");
        for (int i = 0; i < N.length; i++) {
            System.out.format(",%3d", N[i]);
        }
        System.out.println("");
        int [] ret = s.maxSlidingWindow(N, K);
        System.out.print("Ret:    ");
        for (int i = 0; i < ret.length; i++) {
            System.out.format(",%3d", ret[i]);
        }
        System.out.println("");
    }
}
