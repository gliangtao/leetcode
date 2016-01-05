/**
Given an array of n integers where n > 1, nums, return an array output such that output[i] is
equal to the product of all the elements of nums except nums[i].

Solve it without division and in O(n).

For example, given [1,2,3,4], return [24,12,8,6].

Follow up:
Could you solve it with constant space complexity? (Note: The output array does not count as
extra space for the purpose of space complexity analysis.)
*/
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
#if 0
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    int i;
    *returnSize = numsSize;
    int *result = (int *)malloc(sizeof(int)*numsSize);
    result[0] = 1;
    for(i=1; i<numsSize; i++) {
        result[i] = nums[i-1] * result[i-1];
    }
    int t = 1;
    for(i=numsSize-1; i>=0; i--) {
        result[i] *= t;
        t *= nums[i];
    }
    return result;
}
#endif

int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    int* ret = (int*)malloc(sizeof(int) * numsSize);
    if (ret) {
        int i, j, t1, t2;
        for (i = 0; i < numsSize; i++) ret[i] = 1;
        for (i = 0, j = numsSize - 1, t1 = t2 = 1; j >= 0; i++, j--) {
            ret[i] *= t1;
            ret[j] *= t2;
            t1 = ret[i];
            t2 = ret[j];
        }
        if (returnSize) *returnSize = numsSize;
    }
    return ret;
}
