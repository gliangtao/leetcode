/*
Given an array S of n integers, find three integers in S such that the sum is closest to a given
number, target. Return the sum of the three integers. You may assume that each input would have
exactly one solution.

For example, given array S = {-1 2 1 -4}, and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/

#include <stdlib.h>

static int mycmp(const void* p1, const void* p2) {
    return (*((int*)p1) - *((int*)p2));
}

void myqsort(void* base, size_t nel, size_t width, int (*compar)(const void*, const void*)) {
    if (nel > 2) {
        void *p, *q, *r, *end;
        char tmp[width];
        p = base;
        q = p + (nel >> 1) * width;
        end = base + (nel - 1) * width;
        for (r = end; p < r; r -= width) {
            if (r == q) {
                continue;
            }
            if (compar(r, q) < 0) {
                while ((p < r) && ((p == q) || (compar(p, q) < 0))) {
                    p += width;
                }
                if (p >= r) {
                    break;
                }
                memcpy(tmp, r, width);
                memcpy(r, p, width);
                memcpy(p, tmp, width);
                p += width;
                if (p == q) {
                    p += width;
                }
            }
        }

        int cmp = compar(p, q);
        if (cmp != 0) {
            if (cmp < 0) {
                if (p < q) {
                    p += width;
                }
            } else {
                if (p > q) {
                    p -= width;
                }
            }
            if (p != q) {
                memcpy(tmp, p, width);
                memcpy(p, q, width);
                memcpy(q, tmp, width);
            }
        }

        if (p > base + width) {
            myqsort(base, ((p - base) / width), width, compar);
        }
        if (p < end - width) {
            myqsort(p + width, nel - 1 - ((p - base) / width), width, compar);
        }
    } else if (nel == 2) {
        if (compar(base, base + width) > 0) {
            char tmp[width];
            memcpy(tmp, base, width);
            memcpy(base, base + width, width);
            memcpy(base + width, tmp, width);
        }
    }
}

//4ms version if using qsort, 8ms if using myqsort
int threeSumClosest(int* nums, int numsSize, int target) {
    int minDelta = INT_MAX;
    int result = INT_MAX;
    int *p, *q, *r;
    int vp, vq, vr;
    int vtarget;
    if (!nums || (numsSize < 3)) {
        return result;
    }
    myqsort(nums, numsSize, sizeof(nums[0]), mycmp);
    for (r = nums + numsSize - 1; r > nums + 1; r--) {
        vr = *r;
        vtarget = vr - target;
        p = nums;
        q = r - 1;
        vp = *p;
        vq = *q;
        while (p < q) {
            int delta = vtarget + vp + vq;
            int absDelta = abs(delta);
            if (absDelta < minDelta) {
                minDelta = absDelta;
                result = target + delta;
            }
            if (delta < 0) {
                vp = *(++p);
            } else if (delta > 0) {
                vq = *(--q);
            } else {
                return target;
            }
        }
    }
    return result;
}
