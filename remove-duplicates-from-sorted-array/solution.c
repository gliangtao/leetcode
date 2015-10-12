
#if 0
//32ms version
int removeDuplicates(int* nums, int numsSize) {
    int vp;
    int* p;
    int* end;
    int* q;
    int delta;
    p = end = nums + numsSize - 1;
    while (p > nums) {
        vp = *p--;
        q = p;
        while ((p >= nums) && (*p == vp)) {
            p--;
        }
        if ((delta = q - p)) {
            memmove(p + 1, q + 1, (end - q) * sizeof(int));
            numsSize -= delta;
        }
    }
    return numsSize;
}
#endif


#if 0
//36ms version
int removeDuplicates(int* nums, int numsSize) {
    int vp;
    int* p;
    int* end;
    int* q;
    int delta;
    end = nums + numsSize;
    p = nums;
    while (p < end) {
        vp = *p++;
        q = p;
        while ((p < end) && (*p == vp)) {
            p++;
        }
        if ((delta = p - q)) {
            memmove(q, p, (end - p) * sizeof(int));
            numsSize -= delta;
            end -= delta;
            p = q;
        }
    }
    return numsSize;
}
#endif

#if 0
//28ms version
int removeDuplicates(int* nums, int numsSize) {
    int vp;
    int* p;
    int* end;
    int* q;
    int delta = 0;
    end = nums + numsSize;
    p = nums;
    int l = 0;
    int lastDelta = 0;
    int* lastQ = NULL;
    while (p < end) {
        vp = *p++;
        q = p;
        while ((p < end) && (*p == vp)) {
            p++;
        }
        if ((delta = p - q)) {
            if (lastDelta) {
                memmove(lastQ, lastQ + lastDelta, (q - lastQ) * sizeof(int));
            }
            lastQ = q - lastDelta;
            lastDelta += delta;
        }
    }
    if (lastDelta) {
        memmove(lastQ, lastQ + lastDelta, (q - lastQ) * sizeof(int));
    }
    return numsSize - lastDelta;
}
#endif

//12ms version
int removeDuplicates(int* nums, int numsSize) {
    int fixed = 0;
    if (numsSize <= 1) {
        return numsSize;
    }
    for (int i = 1; i < numsSize; i++) {
        if (nums[fixed] != nums[i]) {
            nums[++fixed] = nums[i];
        }
    }
    return fixed + 1;
}

