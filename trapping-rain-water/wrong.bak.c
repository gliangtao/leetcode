#include <stdlib.h>
#include <limits.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>
#ifdef MY_UNIT_TEST
#define DBG(str...) printf(str)

//int HEIGHT[] = { 2,1,0,2 };
//int HEIGHT[] = {5, 4, 1, 2};
//int HEIGHT[] = {5,2,1,2,1,5};
//int HEIGHT[] = {2,0,2};
//int HEIGHT[] = {5,5,1,7,1,1,5,2,7,6};
int HEIGHT[] = {0,1,0,2,1,0,1,3,2,1,2,1};

int trap(int* height, int heightSize);

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int i;
    gettimeofday(&tvStart, NULL);
    i = trap(HEIGHT, sizeof(HEIGHT) / sizeof(HEIGHT[0]));
    gettimeofday(&tvEnd, NULL);
    
    printf("trap: %d, array:\n", i);
    for (int i = 0; i < sizeof(HEIGHT) / sizeof(HEIGHT[0]); i++) {
        printf(",%d", HEIGHT[i]);
    }
    printf("\n");
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    DBG("Time %d.%06d, trap\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif

typedef struct MyNode {
    struct MyNode*  next;
    int             i;
    int             h;
    int             hsum;
} MyNode;

/*
Given n non-negative integers representing an elevation map where the width of each bar is 1,
compute how much water it is able to trap after raining.

For example, 
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.
*/
int trap(int* height, int heightSize) {
    MyNode* head = NULL;
    MyNode** peaks = NULL;
    MyNode* node, *prev;
    int nPeaks = 0;
    int ret = 0;
    if (!height || (heightSize < 3)) {
        goto bail;
    }

    int down = 0;
    int i, hsum = 0, delta, r;

    for (i = 0; i < heightSize - 1; i++) {
        hsum += height[i];
        delta = height[i] - height[i + 1];
        if (delta < 0) {
            if (down) {
                down = 0;
            }
            if (i < heightSize - 2) {
                continue;
            } else {
                i = heightSize - 1;
                hsum += height[i];
            }
        } else if (!delta || down) {
            continue;
        }
        down = 1;
        //height[i] is new peak
        node = (MyNode*)malloc(sizeof(MyNode));
        if (!node) goto bail;
        node->next = head;
        node->i = i;
        node->h = height[i];
        node->hsum = hsum;
        head = node;
        nPeaks++;
    }

    if (nPeaks <= 1) goto bail;

    peaks = (MyNode**)malloc(sizeof(MyNode*) * nPeaks);
    if (!peaks) goto bail;

    MyNode** pp = peaks;

    for (pp = peaks, node = head; node != NULL; node = node->next) *pp++ = node;
/*
    // Build heap
    int limit = (nPeaks >> 1);
    for (i = limit - 1; i >= 0; i--) {
        int top = i;
        while (top < limit) {
            int left = (top << 1) + 1;
            int right = left + 1;
            int maxh = peaks[top]->h;
            int lh = peaks[left]->h;
            int rh = (right >= nPeaks) ? INT_MIN : peaks[right]->h;
            if (max == lh) {
                
            }
            if ((maxh < lh) || (maxh < rh) ||
                ((max == lh) && )) {
                if (lh < rh) {
                    node = peaks[right];
                    peaks[right] = peaks[top];
                    peaks[top] = node;
                    top = right;
                } else {
                    node = peaks[left];
                    peaks[left] = peaks[top];
                    peaks[top] = node;
                    top = left;
                }
            } else {
                break;
            }
        }
    }

    // Sort heap
    prev = peaks[0];
    r = nPeaks - 1;
    peaks[0] = peaks[r];
    while (r > 0) {
        int top = 0;
        while (top < (r >> 1)) {
            int left = (top << 1) + 1;
            int right = left + 1;
            int maxh = peaks[top]->h;
            int lh = peaks[left]->h;
            int rh = (right >= nPeaks) ? INT_MIN : peaks[right]->h;
            if ((maxh < lh) || (maxh < rh)) {
                if (lh < rh) {
                    node = peaks[right];
                    peaks[right] = peaks[top];
                    peaks[top] = node;
                    top = right;
                } else {
                    node = peaks[left];
                    peaks[left] = peaks[top];
                    peaks[top] = node;
                    top = left;
                }
            } else {
                break;
            }
        }
        node = peaks[0];
        if (node->hsum > 0) {
            // Calculate water between prev and node;
            MyNode* q;
            int count = 0;
            int h = node->h;
            int subsum = 0;
            breakme();
            if (node->i < prev->i) {
                for (i = node->i + 1; i < prev->i; i++) {
                    delta = h - height[i];
                    if (delta > 0) {
                        ret += delta;
                        subsum += delta;
                    }
                }
                for (q = prev->next; q && (q != node); q = q->next) {
                    // All the minor peaks between prev and node are under water, skip them
                    q->hsum = -1;
                }
            } else {
                //delta = ((delta - 1) * node->h) - (node->hsum - prev->hsum - node->h);
                for (i = prev->i + 1; i < node->i; i++) {
                    delta = h - height[i];
                    if (delta > 0) {
                        ret += delta;
                        subsum += delta;
                    }
                }
                for (q = node->next; q && (q != prev); q = q->next) {
                    // All the minor peaks between prev and node are under water, skip them
                    q->hsum = -1;
                }
            }
            //ret += delta;
            DBG("subsum %d, h[%d] %d, h[%d] %d, sum %d\n",
                subsum, node->i, node->h, prev->i, prev->h, ret);
            prev = node;
        }

        peaks[0] = peaks[r--];
    }
*/
bail:
    free(peaks);

    for (node = head; node != NULL;) {
        MyNode* next = node->next;
        free(node);
        node = next;
    }

    return ret;

}
