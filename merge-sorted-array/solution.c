
/*
Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:
You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold
additional elements from nums2. The number of elements initialized in nums1 and nums2 are m and n
respectively.
*/
#if 0
//0ms version, O(n)
void merge(int* nums1, int m, int* nums2, int n) {
    if (!nums1 || !nums2 || (n <= 0) || (m < 0)) return;
    if (!m) {
        memcpy(nums1, nums2, n * sizeof(int));
        return;
    }

    memmove(nums1 + n, nums1, m * sizeof(int));

    int *p = nums1;
    int *p1 = nums1 + n;
    int *p2 = nums2;
    int* end1 = nums1 + m + n - 1;
    int *end2 = nums2 + n - 1;
    int v1, v2;

    for (v1 = *p1, v2 = *p2; (p1 <= end1) && (p2 <= end2);) {
        if (v1 <= v2) {
            *p++ = v1;
            v1 = *(++p1);
        } else {
            *p++ = v2;
            v2 = *(++p2);
        }
    }
    if (p1 <= end1) {
        memmove(p, p1, (end1 - p1 + 1) * sizeof(int));
    } else {
        memcpy(p, p2, (end2 - p2 + 1) * sizeof(int));
    }
}
#endif

void merge(int* nums1, int m, int* nums2, int n) {
    if (!nums1 || !nums2 || (n <= 0) || (m < 0)) return;
    if (!m) {
        memcpy(nums1, nums2, n * sizeof(int));
        return;
    }

    int *p = nums1 + m + n - 1;
    int *p1 = nums1 + m - 1;
    int *p2 = nums2 + n - 1;
    int v1, v2;

    for (v1 = *p1, v2 = *p2; (p1 >= nums1) && (p2 >= nums2);) {
        if (v1 > v2) {
            *p-- = v1;
            v1 = *(--p1);
        } else {
            *p-- = v2;
            v2 = *(--p2);
        }
    }
    if (p2 >= nums2) {
        memcpy(nums1, nums2, (p2 - nums2 + 1) * sizeof(int));
    }
}

