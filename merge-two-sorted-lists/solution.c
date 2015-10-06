/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
//4ms version
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode fakeNode;
    struct ListNode* p;
    fakeNode.next = NULL;
    p = &fakeNode;
    while (l1 && l2) {
        if (l1->val < l2->val) {
            p = p->next = l1;
            l1 = l1->next;
        } else {
            p = p->next = l2;
            l2 = l2->next;
        }
    }
    if (!l1) {
        p->next = l2;
    } else {
        p->next = l1;
    }
    return fakeNode.next;
}
