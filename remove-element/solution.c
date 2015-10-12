//0ms version
int removeElement(int* nums, int numsSize, int val) {
    int i;
    if (!nums || numsSize <= 0) {
        return 0;
    }
    int fixed = 0;
    for (i = 0; i < numsSize; i++) {
        if (nums[i] != val) {
            nums[fixed++] = nums[i];
        }
    }
    return fixed;
}
