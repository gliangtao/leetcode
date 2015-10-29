/**
Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
//4ms version, O(n)
struct ListNode* rotateRight(struct ListNode* head, int k) {
    if (!head || !k) return head;

    struct ListNode* p = head, *prev;
    int size = 0;
    do {
        prev = p;
        size++;
        p = p->next;
    } while (p != NULL);

    k = k % size;

    if (k) {
        int i;
        for (i = size - k - 1, p = head; i > 0; i--) {
            p = p->next;
        }
        prev->next = head;
        head = p->next;
        p->next = NULL;
    }
    return head;
}
