package SlidingWindowMax;

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

    private static class DqNode {
        public DqNode(int nid, int nval) {
            this.nid = nid;
            this.nval = nval;
        }
        int nid;
        int nval;
    }

    private static class Dq {
        private void compactNodes(int minNid) {
            DqNode[] tmp = new DqNode[K];
            int i, j;
            //head == tail;
            for (i = head, j = -1; i < K; i++) {
                if (nodes[i].nid >= minNid) tmp[++j] = nodes[i];
            }
            for (i = 0; i < head; i++) {
                if (nodes[i].nid >= minNid) tmp[++j] = nodes[i];
            }
            head = 0;
            tail = j;
            nodes = tmp;
        }

        public int addNode(int nid, int nval) {
            int ret;
            int minNid = nid - k;
            DqNode node = new DqNode(nid, nval);
            int ntail = (tail - 1) & (K - 1);
            while ((head != tail) && (nodes[head].nid <= minNid)) head = (head + 1) & (K - 1);
            while ((head != tail) && ((nodes[ntail].nval <= nval) || (nodes[ntail].nid <= minNid))) {
                tail = ntail;
                ntail = (ntail - 1) & (K - 1);
            }
            if (head == tail) {
                nodes[tail] = node;
                tail = (tail + 1) & (K - 1);
                ret = nval;
            } else if (nval > nodes[head].nval) {
                ret = nval;
                nodes[head = (head - 1) & (K - 1)] = node;
            } else if (nval == nodes[head].nval) {
            	ret = nval;
            	nodes[head].nid = nid;
            } else {
                ret = nodes[head].nval;
                nodes[tail] = node;
                tail = (tail + 1) & (K - 1);
            }
            if (head == tail) compactNodes(minNid);
            if (D) {
                int i;
                System.out.print("Nodes:    ");
                if (head < tail) {
                    for (i = head; i < tail; i++) {
                        System.out.format(",%3d", nodes[i].nval);
                    }
                } else {
                    for (i = head; i < K; i++) System.out.format(",%3d", nodes[i].nval);
                    for (i = 0; i < tail; i++) System.out.format(",%3d", nodes[i].nval);
                }
                System.out.println("");
            }
            return ret;
        }

        public Dq(int k) {
            this.k = k;
            K = getK(k);
            nodes = new DqNode[K];
            head = tail = 0;
        }
        DqNode[] nodes;
        int K;
        int k;
        int head;
        int tail;
    }

    private static int getK(int k) {
        if (k < 16) return 16;
        k |= (k >>> 1);
        k |= (k >>> 2);
        k |= (k >>> 4);
        k |= (k >>> 8);
        k |= (k >>> 16);
        k++;
        if (k >= (1 << 30)) throw new RuntimeException("Too big");
        return (k << 1);
    }

    //7-9ms, O(n) time, O(k) space, Deque
    public int[] maxSlidingWindow(int[] nums, int k) {
        int i, j, N = nums.length;
        if ((N <= 0) || (k == 0) || (k > N)) return new int[0];
        Dq dq = new Dq(k);
        for (i = 0; i < k - 1; i++) dq.addNode(i, nums[i]);
        int[] ret = new int[N - k + 1];
        i = 0;
        ret[i++] = dq.addNode(k - 1, nums[k - 1]);
        for (j = k; j < N; j++) ret[i++] = dq.addNode(j, nums[j]);
        return ret;
    }

    private static final boolean D = false;
    //private static final int[] N = { 1,3,1,2,0,5 };
    //private static final int K = 3;
    private static final int[] N = {5183,2271,3067,539,8939,2999,9264,737,3974,5846,-210,9278,5800,2675,6608,1133,-1,6018,9672,5179,9842,7424,-209,2988,2757,5984,1107,2644,-499,7234,7539,6525,347,5718,-742,1797,5292,976,8752,8297,1312,3385,5924,2882,6091,-282,2595,96,1906,8014,7667,5895,7283,7974,-167,7068,3946,6223,189,1589,2058,9277,-302,8157,8256,5261,8067,1071,9470,2682,8197,5632,753,3179,8187,9042,8167,4657,7080,7801,5627,7917,8085,928,-892,-427,3685,4676,2431,8064,8537,343,505,4352};
    private static final int K = 50;
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
