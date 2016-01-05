/**
Given an array of numbers nums, in which exactly two elements appear only once and all the other
elements appear exactly twice. Find the two elements that appear only once.

For example:

Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].

Note:
The order of the result is not important. So in the above example, [5, 3] is also correct.
Your algorithm should run in linear runtime complexity. Could you implement it using only constant
space complexity?
*/

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
#if 0
//4ms O(n) Time O(1) space
int* singleNumber(int* nums, int numsSize, int* returnSize) {
    if (!nums || (numsSize < 2)) return NULL;
    int* ret = (int*)malloc(sizeof(int) * 2);
    if (!ret) return NULL;
    unsigned int i, x = 0;
    for (i = 0; i < numsSize; i++) {
        x ^= nums[i];
    }
    for (i = 0; !(x & 1); x >>= 1, i++);
    x = (1 << i);
    int ret1, ret2;
    for (ret1 = ret2 = i = 0; i < numsSize; i++) {
        register int tmp = nums[i];
        if (tmp & x) ret1 ^= tmp;
        else ret2 ^= tmp;
    }
    ret[0] = ret1;
    ret[1] = ret2;
    if (returnSize) *returnSize = 2;
    return ret;
}
#endif

//4ms O(n) Time O(1) space
int* singleNumber(int* nums, int numsSize, int* returnSize) {
    if (!nums || (numsSize < 2)) return NULL;
    int* ret = (int*)malloc(sizeof(int) * 2);
    if (ret) {
        int i, x = 0, y = 0, flag, tmp;
        for (i = 0; i < numsSize; i++) x ^= nums[i];
        flag = x & -x; //Get last bit of x https://leetcode.com/discuss/52377/3-lines-ruby-4-lines-c
        for (i = 0; i < numsSize; i++) if ((tmp = nums[i]) & flag) y ^= tmp;
        ret[0] = x ^ y;
        ret[1] = y;
        if (returnSize) *returnSize = 2;
    }
    return ret;
}
