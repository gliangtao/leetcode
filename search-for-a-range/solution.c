/*
Given a sorted array of integers, find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].
*/

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
    int* ret = (int*)malloc(2 * sizeof(int));
    if (!ret) {
        if (returnSize) *returnSize = 0;
        printf("ret is NULL\n");
        return NULL;
    }
    int l, r, i, d1, d2, iFound = -1, iFirst, iLast;
    if (!nums) {
        goto not_found;
    }
    for (l = 0, r = numsSize - 1; l <= r;) {
        i = ((l + r) >> 1);
        d1 = nums[i] - target;
        if (d1 < 0) {
            l = i + 1;
        } else if (d1 > 0) {
            r = i - 1;
        } else {
            iFound = i;
            break;
        }
    }

    if (iFound < 0) {
        goto not_found;
    }

    iFirst = 0;
    iLast = numsSize - 1;
    for (l = 0, r = iFound - 1; l <= r;) {
        i = ((l + r) >> 1);
        d1 = nums[i + 1] - target;
        d2 = nums[i] - target;
        if (!d1) {
            if (d2) {
                iFirst = i + 1;
                break;
            }
            r = i - 1;
        } else {
            l = i + 1;
        }
    }
    for (l = iFound, r = numsSize - 2; l <= r;) {
        i = ((l + r) >> 1);
        d1 = nums[i] - target;
        d2 = nums[i + 1] - target;
        if (!d1) {
            if (d2) {
                iLast = i;
                break;
            }
            l = i + 1;
        } else {
            r = i - 1;
        }
    }

    ret[0] = iFirst;
    ret[1] = iLast;
    //printf("Found, range [%d:%d]\n", iFirst, iLast);
    if (returnSize) {
        *returnSize = 2;
    }
    return ret;

not_found:
    ret[0] = ret[1] = -1;
    //printf("NOT_FOUND, range [-1:-1]\n", iFirst, iLast);
    if (returnSize) {
        *returnSize = 2;
    }
    return ret;
}
