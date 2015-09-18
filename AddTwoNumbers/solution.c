/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int nv, carry;
    struct ListNode* p;
    struct ListNode* q;
    struct ListNode* ret;
    struct ListNode* node;
    struct ListNode* last;
    p = l1;
    q = l2;
    carry = 0;
    while (p && q) {
        nv = p->val + q->val + carry;
        if (nv >= 10) {
            nv -= 10;
            carry = 1;
        } else {
            carry = 0;
        }
        p ->val = q->val = nv;
        last = p;
        p = p->next;
        q = q->next;
    }
    if (!p && q) {
        p = q;
        ret = l2;
    } else {
        ret = l1;
    }
    while (p) {
        nv = p->val + carry;
        if (nv >= 10) {
            nv -= 10;
            carry = 1;
        } else {
            carry = 0;
        }
        p->val = nv;
        last = p;
        p = p->next;
    }
    if (carry) {
        p = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (p) {
            p->val = carry;
            p->next = NULL;
            last->next = p;
        } else {
            ret = NULL;
        }
    }
    return ret;
}
