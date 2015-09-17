/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target) {
    int max = 0;
    int t;
    int *p = nums;
    for (int i = 0; i < numsSize; i++) {
        *p = t = (*p << 1) - target;
        if (t < 0) {
            t = -t;
        }
        if (t > max) {
            max = t;
        }
        p++;
    }
    int* ht = (int*)malloc(sizeof(int) * (max + 1));
    if (!ht) {
        return NULL;
    }
    for (int i = 0; i <= max; i++) {
        ht[i] = -1;
    }
    for (int i = 0; i < numsSize; i++) {
        int t = nums[i];
        if (t < 0) {
            t = -t;
        }
        if (ht[t] >= 0) {
            if (nums[ht[t]] + nums[i] == 0) {
                int *ret = (int*)malloc(sizeof(int) * 2);
                if (ret) {
                    ret[0] = ht[t] + 1;
                    ret[1] = i + 1;
                }
                free(ht);
                return ret;
            }
        }
        ht[t] = i;
    }
    free(ht);
    return NULL;
}
