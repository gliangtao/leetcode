/*
Given a set of non-overlapping intervals, insert a new interval into the intervals
(merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
*/

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
//572ms version
struct Interval* insert(struct Interval* intervals, int intervalsSize, struct Interval newInterval, int* returnSize) {
    struct Interval* ret = (struct Interval*)malloc(sizeof(struct Interval) * (intervalsSize + 1));
    int retSize = 0;
    if (ret) {
        int start = newInterval.start;
        int end = newInterval.end;
        struct Interval* p = ret - 1;
        struct Interval* next = intervals;
        struct Interval* pend = intervals + intervalsSize;

        if (!intervals || !intervalsSize || (end < next->start)) {
            *(++p) = newInterval;           //No merge needed, almost ready to return
        } else {
            while ((next < pend) && (next->end < start)) *(++p) = *next++;
            if (next < pend) {
                if (end < next->start) {
                    *(++p) = newInterval;   //No merge needed, almost ready to return
                } else {
                    *(++p) = *next++;       //Merge next + newInterval into (++p)
                    if (start < p->start) {
                        p->start = start;
                    }
                    if (p->end < end) {
                        p->end = end;
                    }
                    while ((next < pend) && (next->start <= p->end)) {
                        if (p->end < next->end) p->end = next->end;
                        next++;
                    }
                }
            } else {
                //Not merged yet. newInterval will be new last-one
                *(++p) = newInterval;
            }
        }
        retSize = (int)(p - ret) + 1;
        if (next < pend) {
            memcpy(p + 1, next, ((size_t)(pend - next)) * sizeof(struct Interval));
            retSize += (int)(pend - next);
        }
    }
    if (returnSize) *returnSize = retSize;
    return ret;
}
