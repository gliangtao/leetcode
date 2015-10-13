
/**
 * Implement next permutation, which rearranges numbers into the lexicographically next greater
 * permutation of numbers. If such arrangement is not possible, it must rearrange it as the lowest
 * possible order (ie, sorted in ascending order). The replacement must be in-place, do not
 * allocate extra memory.
 *
 * Here are some examples. Inputs are in the left-hand column and its corresponding outputs are
 * in the right-hand column.
 * 1,2,3 → 1,3,2
 * 3,2,1 → 1,2,3
 * 1,1,5 → 1,5,1
*/

static int mycmp(const void* p1, const void* p2) {
    return (*((int*)p1) - *((int*)p2));
}

void nextPermutation(int* nums, int numsSize) {
    int *last = nums + numsSize - 1, *p = last, *q;
    int t;
    while ((p > nums) && (p[-1] >= *p)) p--;

    if (p != last) {
        if ((p > nums) && (p != last)) {
            t = p[-1];
            q = last;
            while (*q <= t) q--;
            p[-1] = *q;
            *q = t;
        }
        qsort(p, last - p + 1, sizeof(int), mycmp);
    } else if (p != nums) {
        t = p[-1];
        p[-1] = *p;
        *p = t;
    }
}
