/*
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.
*/
#define IDX(i)  (((i + c) < 0) ? (i + pivot) : (i + c))
int search(int* nums, int numsSize, int target) {
    int x, d, i, l, r, pivot, c;

    if (!nums) {
        return -1;
    }
    for (l = 1, r = numsSize - 1, x = nums[0]; l <= r;) {
        i = (l + r) >> 1;
        if (nums[i] < x) {
            r = i - 1;
        } else {
            l = i + 1;
        }
    }
    pivot = l;

    //if (pivot == numsSize) pivot = 0; //Actually, the "if" can be kept but better be removed
    c = pivot - numsSize;
    //printf("n%d %d, pivot n%d %d\n", r, nums[r], pivot, nums[pivot]);
    for (l = 0, r = numsSize - 1; l <= r;) {
        i = (l + r) >> 1;
        int ri = IDX(i);
        d = nums[ri] - target;
        //printf("N(%d) (n[%d]) - target = %d - %d = %d\n", i, ri, d + target, target, d);
        if (d < 0) {
            l = i + 1;
        } else if (d > 0) {
            r = i - 1;
        } else return ri;
    }
    return -1;
}
