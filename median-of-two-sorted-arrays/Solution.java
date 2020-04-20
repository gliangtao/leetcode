class Solution {
    double doFind(int[] nums1, int[] nums2, int M, int N) {
        final int T = ((M + N + 1) >> 1);
        int low, high, mid1 = 0, mid2 = 0;
        for (low = 0, high = M; low <= high;) {
            mid1 = ((high + low) >> 1);
            mid2 = T - mid1;
            if ((mid1 < high) && (nums1[mid1] < nums2[mid2 - 1])) {
                low = mid1 + 1;
            } else if ((mid1 > low) && (nums1[mid1 - 1] > nums2[mid2])) {
                high = mid1 - 1;
            } else {
                break;
            }
        }
        /// nums1: 0, 1, ... mid1-1, | mid1, mid1+1, ... M-1
        /// nums2: 0, 1, ... mid2-1, | mid2, mid2+1, ... N-1
        int maxLeft;
        if (mid1 == 0) {
            maxLeft = nums2[mid2 - 1];
        } else if (mid2 == 0) {
            maxLeft = nums1[mid1 - 1];
        } else {
            maxLeft = Math.max(nums1[mid1 - 1], nums2[mid2 - 1]);
        }
        if (((M + N) & 1) == 1) {
            return (double)maxLeft;
        }
        int minRight;
        if (mid1 == M) {
            minRight = nums2[mid2];
        } else if (mid2 == N) {
            minRight = nums1[mid1];
        } else {
            minRight = Math.min(nums1[mid1], nums2[mid2]);
        }
        return (minRight + maxLeft) * 0.5;
    }
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        final int M = nums1.length;
        final int N = nums2.length;
        return (M < N) ? doFind(nums1, nums2, M, N) : doFind(nums2, nums1, N, M);
    }
}
