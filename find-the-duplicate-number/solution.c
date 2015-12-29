/**
Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive),
prove that at least one duplicate number must exist. Assume that there is only one duplicate number,
find the duplicate one.

Note:
You must not modify the array (assume the array is read only).
You must use only constant, O(1) extra space.
Your runtime complexity should be less than O(n2).
There is only one duplicate number in the array, but it could be repeated more than once.
*/
//4ms
int findDuplicate(int* nums, int numsSize) {
    if (!nums || (numsSize <= 0)) return -1;
    int slow, fast, match;
    slow = fast = 0;
    do {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (fast != slow);
    for (match = 0; match != slow;) {
        slow = nums[slow];
        match = nums[match];
    }
    return match;
}
