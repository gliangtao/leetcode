#include <stdlib.h>

//This is one 388ms version
static int fixHeap(struct ListNode** lists, int listsSize, int i) {
    int left = (i << 1) + 1;
    int right = left + 1;
    int min;
    struct ListNode* t;
    if (!lists[i]) {
        lists[i] = lists[--listsSize];
    }
    while (left < listsSize) {
        min = ((right < listsSize) && ((lists[right]->val - lists[left]->val) < 0)) ? right : left;
        if ((lists[min]->val - lists[i]->val) < 0) {
            t = lists[i];
            lists[i] = lists[min];
            lists[min] = t;
            i = min;
            left = (min << 1) + 1;
            right = left + 1;
        } else {
            break;
        }
    }
    return listsSize;
}

static int buildHeap(struct ListNode** lists, int listsSize) {
    for (int i = (listsSize - 2) >> 1; i >= 0; i--) {
        fixHeap(lists, listsSize, i);
    }
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
//This is one 388ms version
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    struct ListNode fakeNode;
    struct ListNode* p;
    struct ListNode** ppl;
    struct ListNode** ppr;
    fakeNode.next = NULL;
    if (!lists) {
        return NULL;
    }
    ppr = lists + listsSize - 1;
    ppl = lists;
    while (1) {
        while ((ppl <= ppr) && (*ppr == NULL)) ppr--;
        if (ppl >= ppr) {
            break;
        }
        if (*ppl++ == NULL) {
            ppl[-1] = *ppr;
            *ppr-- = NULL;
        }
    }
    listsSize = (ppr - lists) + 1;
    if (listsSize == 0) {
        return NULL;
    }
    if (listsSize == 1) {
        return *lists;
    }
    buildHeap(lists, listsSize);
    p = &fakeNode;
    do {
        p->next = *lists;
        p = p->next;
        *lists = p->next;
        listsSize = fixHeap(lists, listsSize, 0);
    } while (listsSize > 1);
    p->next = lists[0];
    return fakeNode.next;
}
