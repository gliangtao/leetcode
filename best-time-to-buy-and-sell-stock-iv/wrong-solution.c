/**
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most k transactions.

Note:
You may not engage in multiple transactions at the same time
(ie, you must sell the stock before you buy again).
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>


#ifdef GLT_UNIT_TEST_VERBOSE
#define VDBG(str...)    printf(str)
static void mydbg()     {}
#else
#define VDBG(str...)
#define mydbg()
#endif

#ifdef GLT_UNIT_TEST
int maxProfit(int k, int* prices, int pricesSize);
int PRICES[] = { 1,2,4,2,5,7,2,4,9,0 };

int PRICES_K = 2;
int PRICES_SIZE = sizeof(PRICES) / sizeof(PRICES[0]);

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int profit;
    gettimeofday(&tvStart, NULL);
    profit = maxProfit(PRICES_K, PRICES, PRICES_SIZE);
    gettimeofday(&tvEnd, NULL);

    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("maxProfit(%d, size %d): time %d.%06d seconds, max %d profit\n",
            PRICES_K, PRICES_SIZE, ds, dus, profit);
    return 0;
}
#endif

typedef struct {
    int* h;
    int size;
    int capacity;
} Heap;

static void initHeap(Heap* heap, int k) {
    heap->h = (int*)malloc(k * sizeof(int));
    if (NULL == heap->h) {
        abort();
        exit(-1);
    }
    heap->size = 0;
    heap->capacity = k;
}

static void finiHeap(Heap* heap) {
    free(heap->h);
}

static void fixHeap(int* hbuf, int i, int k) {
    int l, r, vi, vl, vr, d;
    l = i + i + 1;
    r = l + 1;
    while (l < k) {
        vi = hbuf[i];
        vl = hbuf[l];
        if (r >= k) {
            if (vi > vl) {
                hbuf[i] = hbuf[l];
                hbuf[l] = vi;
            }
            return;
        }
        vl = hbuf[l];
        vr = hbuf[r];
        d = vl - vr;
        if (d > 0) vl = vr;
        if (vi > vl) {
            hbuf[i] = vl;
            i = l + !(d <= 0);
            hbuf[i] = vi;
            l = i + i + 1;
            r = l + 1;
        } else {
            return;
        }
    }
}

static void add2Heap(Heap* heap, int newVal) {
    if (heap->size < heap->capacity) {
        heap->h[heap->size++] = newVal;
        if (heap->size == heap->capacity) {
            int i;
            for (i = ((heap->size - 1) >> 1); i >= 0; i--) {
                fixHeap(heap->h, i, heap->size);
            }
        }
    } else if (newVal > heap->h[0]) {
        heap->h[0] = newVal;
        fixHeap(heap->h, 0, heap->size);
    }
}

static int getHeapSum(Heap* heap) {
    int i, sum = 0;
    for (i = heap->size - 1; i >= 0; i--) sum += heap->h[i];
    return sum;
}

int maxProfit(int k, int* prices, int pricesSize) {
    if (!prices || (pricesSize <= 0) || (k <= 0)) return 0;
    if (k > pricesSize) k = pricesSize;

    const int K = k;
    Heap heap;
    initHeap(&heap, k);
    int i, d, t;

    for (i = 1; i < pricesSize;) {
        t = 0;
        while ((i < pricesSize) && ((d = (prices[i] - prices[i - 1])) >= 0)) {
            t += d;
            i++;
        }
        if (t > 0) add2Heap(&heap, t);
        while ((i < pricesSize) && ((d = (prices[i] - prices[i - 1])) < 0)) {
            i++;
        }
    }
    int ret = getHeapSum(&heap);
    finiHeap(&heap);

    return ret;
}


