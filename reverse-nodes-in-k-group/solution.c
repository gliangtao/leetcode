/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    struct ListNode fakeNode;
    struct ListNode *q, *prek, *nextk, *p, *r;
    int i;
    if (!head || (k <= 1)) {
        return head;
    }
    fakeNode.next = head;
    prek = &fakeNode;
    p = prek;
    q = p->next;
    while (q != NULL) {
        for (i = k; i > 0; i--) {
            if (q == NULL) {
                break;
            }
            r = q->next;
            q->next = p;
            p = q;
            q = r;
        }
        if (i > 0) {
            q = p->next;
            p->next = NULL;
            prek->next = p;
            for (; i < k; i++) {
                r = q->next;
                q->next = p;
                p = q;
                q = r;
            }
            break;
        }
        nextk = prek->next;
        nextk->next = q;
        prek->next = p;
        p = prek = nextk;
    }
    return fakeNode.next;
}
