/*
Given an array with n objects colored red, white or blue, sort them so that objects of the same
color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.

click to show follow up.

Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total
number of 0's, then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?
*/
#if 0
//0ms, Counting sort, O(n) time, O(1) space
void sortColors(int* nums, int numsSize) {
    if (!nums || (numsSize <= 0)) return;

    int c[3], i, j, *p;
    memset(c, 0, sizeof(c));
    for (i = numsSize - 1; i >= 0; i--) {
        c[nums[i]] += 1;
    }
    for (i = (sizeof(c) / sizeof(c[0])) - 1, p = nums + numsSize - 1; i >= 0; i--) {
        for (j = c[i] - 1; j >= 0; j--) {
            *p-- = i;
        }
    }
}
#endif

#if 0
static int myqselect(int* nums, int l, int r, int target) {
    int i;
    for (i = r; r >= l; r--) {
        if (nums[r] == target) {
            if (r != i) {
                register int t = nums[i];
                nums[r] = t;
                nums[i] = target;
            }
            i--;
        }
    }
    return i;
}

//0ms, Quick select, 2-pass, O(n) time, O(1) space
void sortColors(int* nums, int numsSize) {
    if (!nums || (numsSize <= 0)) return;

    int r = myqselect(nums, 0, numsSize - 1, 2);
    myqselect(nums, 0, r, 1);
}
#endif

stati

//0ms, 3-div, O(n) time, O(1) space
void sortColors(int* nums, int numsSize) {
    if (!nums || (numsSize <= 0)) return;

    int r = numsSize - 1, l = 0, i;

    for (i = l; i <= r;) {
        switch (nums[i]) {
            case 0:
                nums[i++] = nums[l];
                nums[l++] = 0;
                break;
            case 1:
                i++;
                break;
            case 2:
                nums[i] = nums[r];
                nums[r--] = 2;
                break;
            default:
                i++;
                break;
        }
    }
}
