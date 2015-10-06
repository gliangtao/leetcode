/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    if (!head || (n <= 0)) {
        return head;
    }
    const int N = n + 1;
    struct ListNode* q[N];
    struct ListNode* p;
    memset(q, 0, sizeof(struct ListNode*) * N);
    int qt, qh;
    qh = qt = 0;
    p = head;
    while (p != NULL) {
        q[qt] = p;
        p = p->next;
        if (++qt == N) {
            qt = 0;
        }
        if (qh == qt) {
            if (++qh == N) {
                qh = 0;
            }
        }
    }
    if (q[qh] != head) {
        if (q[qt] != NULL) {
            q[qt]->next = q[qh]->next;
        }
    } else {
        head = head->next;
    }
    return head;
}
