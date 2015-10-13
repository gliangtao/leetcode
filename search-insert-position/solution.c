#if 0
//4ms version
int searchInsert(int* nums, int numsSize, int target) {
    int l, r, i;
    if (!nums) {
        return -1;
    }
    l = 0;
    r = numsSize - 1;
    if (target <= nums[l]) return 0;
    if (target > nums[r]) return numsSize;
    while (l <= r) {
        i = ((l + r) >> 1);
        if (target < nums[i]) {
            r = i - 1;
        } else if (target > nums[i]) {
            l = i + 1;
        } else {
            return i;
        }
    }
    return l;
}
#endif

//4ms version
int searchInsert(int* nums, int numsSize, int target) {
    int l, r, i, d;
    if (!nums) {
        return -1;
    }
    for (l = 0, r = numsSize - 1; l <= r;) {
        i = ((l + r) >> 1);
        d = target - nums[i];
        if (d < 0) {
            r = i - 1;
        } else if (d > 0) {
            l = i + 1;
        } else {
            return i;
        }
    }
    return l;
}
