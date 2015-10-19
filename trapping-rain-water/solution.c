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
//int HEIGHT[] = {0,1,0,2,1,0,1,3,2,1,2,1};
//int HEIGHT[] = {6,4,2,0,3,2,0,3,1,4,5,3,2,7,5,3,0,1,2,1,3,4,6,8,1,3};
//int HEIGHT[] = {5, 3, 7, 7};
//int HEIGHT[] = {5,2,1,2,1,5};
int HEIGHT[] = {4,2,0,3,2,5};

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

#if 0
typedef struct MyNode {
    struct MyNode*  next;
    int             i;
    int             h;
} MyNode;

/*
Given n non-negative integers representing an elevation map where the width of each bar is 1,
compute how much water it is able to trap after raining.

For example, 
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.
*/
//4ms version
int trap(int* height, int heightSize) {
    MyNode *node, *head = NULL;
    int nPeaks = 0, ret = 0;
    if (!height || (heightSize < 3)) {
        goto bail;
    }

    int i, delta, r, down = 0;

    for (i = 0; i < heightSize - 1; i++) {
        delta = height[i] - height[i + 1];
        if (delta <= 0) {
            if (down) {
                down = 0;
            }
            if (i < heightSize - 2) {
                continue;
            } else {
                i = heightSize - 1;
            }
        } else if (down) {
            continue;
        }
        down = 1;
        //height[i] is new peak
        node = (MyNode*)malloc(sizeof(MyNode));
        if (!node) goto bail;
        node->next = head;
        node->i = i;
        node->h = height[i];
        head = node;
        nPeaks++;
    }

    if (nPeaks <= 1) goto bail;

    MyNode *pl, *pm, *pn;

    pl = head;
    pm = head->next;

    while (pm != NULL) {
        int h = pl->h;
        if (h < pm->h) {
            pl = pm;
            pm = pm->next;
            continue;
        }
        pn = pm->next;
        //Make sure pm is next real peak
        while (pn != NULL) {
            if (pm->h < pn->h) {
                pl->next = pn;
                free(pm);
                pm = pn;
                if (h <= pm->h) break;
            }
            pn = pn->next;
        }

        pl = pm;
        pm = pm->next;
    }

    pl = head;
    pm = head->next;
    while (pm != NULL) {
        int h = (pl->h < pm->h) ? pl->h : pm->h;
        r = pl->i;
        DBG("h[%d] (%d)  -> h[%d] (%d), ret %d, h %d, array:", pm->i, pm->h, pl->i, pl->h, ret, h);
        for (i = pm->i + 1; i < r; i++) {
            DBG(",%d", height[i]);
            delta = h - height[i];
            if (delta > 0) ret += delta;
        }
        DBG("\nNow ret -> %d\n", ret);
        pl = pm;
        pm = pm->next;
    }

bail:
    for (node = head; node != NULL;) {
        MyNode* next = node->next;
        free(node);
        node = next;
    }

    return ret;

}
#endif


#ifndef DBG
#define DBG(str...)
#endif

//4ms version, O(N) time, O(1) space
int trap(int* height, int heightSize) {
    int nPeaks = 0, ret = 0;
    if (!height || (heightSize < 3)) {
        goto bail;
    }

    int i, j, h, delta;

    int imax, inextmax, valley = 0;
    for (i = 1, imax = 0; i < heightSize; i++) {
        if (height[i] >= height[imax]) {
            if (valley) {
                valley = 0;
                h = height[imax];
                DBG("A: h[%d] (%d)  -> h[%d] (%d), ret %d, h %d, array:",
                    imax, height[imax], i, height[i], ret, h);
                for (j = imax + 1; j < i; j++) {
                    DBG(",%d", height[j]);
                    delta = h - height[j];
                    if (delta > 0) ret += delta;
                }
                DBG("\nNow ret -> %d\n", ret);
            }
            imax = i;
        } else {
            if (!valley) valley = 1;
            for (j = i + 1, inextmax = i; j < heightSize; j++) {
                if (height[j] > height[inextmax]) {
                    inextmax = j;
                    if (height[j] >= height[imax]) break;
                }
            }
            h = (height[imax] > height[inextmax]) ? height[inextmax] : height[imax];
            DBG("B: h[%d] (%d)  -> h[%d] (%d), ret %d, h %d, array:",
                imax, height[imax], inextmax, height[inextmax], ret, h);
            for (j = imax + 1; j < inextmax; j++) {
                DBG(",%d", height[j]);
                delta = h - height[j];
                if (delta > 0) ret += delta;
            }
            DBG("\nNow ret -> %d\n", ret);
            i = imax = inextmax;
        }
    }

bail:
    return ret;

}

