
//My solution
#ifdef MY_UNIT_TEST
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NOE(a)  (sizeof(a)/sizeof(a[0]))
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size);

int main(int argc, char** argv)
{
    int* buf = (int*)malloc(sizeof(int) * 1024 * 1024);
    if (!buf) {
        return -1;
    }
    int* nums1;
    int* nums2;
    int nums1Size;
    int nums2Size;
    char* tok;
    char* p = argv[1];
    int* p1 = buf;
    int* p2;
    while ((tok = strsep(&p, ", ")) && *tok) {
        *(p1++) = strtol(tok, NULL, 0);
    }
    p2 = p1;
    p = argv[2];
    nums1 = buf;
    nums2 = p1;
    while ((tok = strsep(&p, ", ")) && *tok) {
        *(p2++) = strtol(tok, NULL, 0);
    }
    nums1Size = (int)(p1 - buf);
    nums2Size = (int)(p2 - p1);
    printf("p1:");
    for (int i = 0; i < nums1Size; i++) {
        printf(" %d ", nums1[i]);
    }
    printf("\n");
    printf("p2:");
    for (int i = 0; i < nums2Size; i++) {
        printf(" %d ", nums2[i]);
    }
    printf("\n");
    printf("%lf\n", findMedianSortedArrays(nums1, nums1Size, nums2, nums2Size));
    free(buf);
    return 0;
}
static void breakme() { }
#endif

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    if (nums2Size < nums1Size) {
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    }
    if (!nums1 || !nums1Size) {
        return (double)(nums2[nums2Size >> 1] + nums2[(nums2Size - 1)  >> 1]) / 2.0;
    }

    int s1 = 0;
    int e1 = nums1Size;
    int s2 = 0;
    int e2 = nums2Size;
    int i1 = (s1 + e1) >> 1;
    int i2;
    int mid = (nums1Size + nums2Size - 1) >> 1;
    i2 = mid - i1;

    int dir = 0;
    while (s1 < e1) {
        if (nums1[i1] < nums2[i2]) {
            s1 = i1 + 1;
            i1 = (s1 + e1) >> 1;
            i2 += (s1 - 1 - i1);
            dir = -1;
        } else if (nums1[i1] == nums2[i2]) {
            return (double)(nums1[i1]);
        } else {
            e1 = i1;
            i1 = (s1 + e1) >> 1;
            i2 += (e1 - i1);
            dir = 1;
        }
    }

    int t0;
    int t1;

    if (dir < 0) {
        i1--;
        i2++;
    }
    if (dir < 0) {
        //nums1[i1], nums2[i2], nums1[i1 + 1], nums2[i2 - 1]
        if ((i2 == 0) || (nums2[i2 - 1] < nums1[i1])) {
            t0 = nums1[i1];
        } else {
            t0 = nums2[i2 - 1];
        }

        if ((i1 == nums1Size - 1) || (nums2[i2] < nums1[i1 + 1])) {
            t1 = nums2[i2];
        } else {
            t1 = nums1[i1 + 1];
        }
    } else {
        //nums1[i1 - 1], nums1[i1], nums2[i2], nums2[i2 + 1]
        if ((i1 == 0) || (nums1[i1 - 1] < nums2[i2])) {
            t0 = nums2[i2];
        } else {
            t0 = nums1[i1 - 1];
        }

        if ((i2 == (nums2Size - 1)) || (nums1[i1] < nums2[i2 + 1])) {
            t1 = nums1[i1];
        } else {
            t1 = nums2[i2 + 1];
        }
    }

    if ((nums1Size + nums2Size) & 1) {
        return (double)(t0);
    }
    return (double)(t0 + t1) / 2.0;
}

#if 0
//LianWei's solution
double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size) {
int m, n;
int total = nums1Size + nums2Size;
int left1max, left2max, right1min, right2min, leftmax, rightmin;
int left1, left2, right1, right2;
int result = 0;

if (nums1Size > nums2Size)
    return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);

if (nums1Size == 0) {
    if (nums2Size & 0x1) {
        return nums2[(nums2Size + 1) / 2 - 1];
    } else {
        return (nums2[(nums2Size + 1) / 2 - 1] + nums2[(nums2Size + 1) / 2]) / 2.0;
    }
}

n = (nums2Size + 1) / 2;
m = (nums1Size + nums2Size + 1) / 2 - n;

left1 = m;
right1 = nums1Size;
left2 = n;
right2 = nums2Size;

while (1) {
    left1max = m > 0 ? nums1[m - 1] : 0;
    left2max = n > 0 ? nums2[n - 1] : 0;
    right1min = m < nums1Size ? nums1[m] : INT_MAX;
    right2min = n < nums2Size ? nums2[n] : INT_MAX;
    if (left1max > right2min) {
        int move = (m - left1 + 1 ) / 2 ? : 1;
        m = m - move;
        n = n + move;
        left1 = m;
        right2 = n;
    } else if (left2max > right1min) {
        int move = (right1 - m) / 2 ? : 1;
        m = m + move;
        n = n - move;
        left2 = n;
        right1 = m;
    } else
        break;
}

leftmax = left1max > left2max ? left1max : left2max;
rightmin = right1min < right2min ? right1min : right2min;

if (total & 0x1)
    return leftmax;
else
    return (leftmax + rightmin) / 2.0;
}

#endif

#if 0
//Another solution
double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size) {
    if (nums2Size < nums1Size) {
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    }

    int low = 0, high = nums2Size, count1 = 0, count2 = 0, mid = (nums1Size+nums2Size)/2 + 1; 

    int find_index_to_insert(int num, int *nums, int size) {
        int lo = 0, hi = size;
        while(lo != hi-1) {
            int index = (lo+hi) / 2;
            if(nums[index] >= num) {
                hi = index;
            } else {
                lo = index;
            }
        }
        return (nums[lo] > num) ? lo : lo+1;
    }

    while (count1 + count2 != mid) { // pick count1 elements from nums1 and count2 elements from nums2
        if (count1 == nums1Size) {
            count2 = mid - count1;
            break;
        }
        if (low == high) {
            count1 = mid - count2;
            break;
        }
        int index2 = (low+high) / 2;
        int index1 = find_index_to_insert(nums2[index2], nums1+count1, nums1Size-count1);
        if (count1+index1 + index2+1 > mid) {
            high = index2;
        } else {
            count1 += index1;
            low = count2 = index2+1;
        }
    }

    if((nums1Size+nums2Size) % 2 == 0) { // take care of all the cases
        if(count1 == 0) return ((double)nums2[count2-1]+nums2[count2-2])/2;
        if(count2 == 0) return ((double)nums1[count1-1]+nums1[count1-2])/2;
        int first, second;
        if(nums1[count1-1] > nums2[count2-1]) {
            first = nums1[count1-1];
            second = nums2[count2-1];
        } else {
            first = nums2[count2-1];
            second = nums1[count1-1];
        } if(count1 >= 2) {
            second = (second > nums1[count1-2]) ? second : nums1[count1-2];
        } if(count2 >= 2) {
            second = (second > nums2[count2-2]) ? second : nums2[count2-2];
        }
        return ((double)first+second)/2;
    }
    if(count1 == 0) return (double)nums2[count2-1];
    if(count2 == 0) return (double)nums1[count1-1];

    return (double)(nums2[count2-1] > nums1[count1-1] ? nums2[count2-1] : nums1[count1-1]);
}


#endif
