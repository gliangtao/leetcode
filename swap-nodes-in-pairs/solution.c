#define MY_K 2
//0ms version
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* swapPairs(struct ListNode* head) {
    struct ListNode *pa[MY_K + 1];
    struct ListNode fakeNode;
    struct ListNode* prek;
    prek = &fakeNode;
    fakeNode.next = head;
    fakeNode.val = INT_MIN;
    int i;
    while (head != NULL) {
        for (i = MY_K; i > 0; i--) {
            pa[i] = head;
            if (head != NULL) {
                head = head->next;
            } else {
                break;
            }
        }
        if (i <= 0) {
            pa[0] = prek;
            for (i = 0; i < MY_K; i++) {
                pa[i]->next = pa[i + 1];
            }
            prek = pa[MY_K];
        } else {
            if (i != MY_K) {
                prek->next = pa[MY_K];
                prek = pa[i + 1];
            }
        }
    }
    prek->next = NULL;
    return fakeNode.next;
}

