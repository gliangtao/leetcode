/**
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.
The algorithm should run in linear time and in O(1) space.
*/
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* majorityElement(int* nums, int numsSize, int* returnSize) {
    if (!nums || (numsSize <= 0)) return NULL;
    int* ret = (int*)malloc(sizeof(int) * 2);
    int i, n1, n2, c1, c2, d1, d2, nRet = 0;
    for (i = c1 = c2 = 0; i < numsSize; i++) {
        if (c1 && (n1 == nums[i])) {
            c1++;
            continue;
        }
        if (c2 && (n2 == nums[i])) {
            c2++;
            continue;
        }
        if (!c1) {
            n1 = nums[i];
            c1 = 1;
            continue;
        }
        if (!c2) {
            n2 = nums[i];
            c2 = 1;
            continue;
        }
        c1--;
        c2--;
    }
    for (i = d1 = d2 = 0; i < numsSize; i++) {
        if ((c1 > 0) && (nums[i] == n1)) d1++;
        if ((c2 > 0) && (nums[i] == n2)) d2++;
    }
    i = numsSize / 3;
    if (d1 > i) ret[nRet++] = n1;
    if (d2 > i) ret[nRet++] = n2;
    if (returnSize) *returnSize = nRet;
    return ret;
}
