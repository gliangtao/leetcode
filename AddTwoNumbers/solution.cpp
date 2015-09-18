/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;
        int nv;
        ListNode* ret = NULL;
        ListNode* tail = NULL;
        if (!l1) {
            return l2;
        }
        if (!l2) {
            return l1;
        }
        ListNode* p;
        ListNode* q;
        ListNode* node;
        p = l1;
        q = l2;
        while (p && q) {
            nv = p->val + q->val + carry;
            if (nv >= 10) {
                nv -= 10;
                carry = 1;
            } else {
                carry = 0;
            }
            if (node = new ListNode(nv)) {
                if (!tail) {
                    ret = node;
                } else {
                    tail->next = node;
                }
                tail = node;
            } else {
                return NULL;
            }
            p = p->next;
            q = q->next;
        }
        if (!p) {
            p = q;
        }
        while (p) {
            nv = p->val + carry;
            if (nv >= 10) {
                nv -= 10;
                carry = 1;
            } else {
                carry = 0;
            }
            if (node = new ListNode(nv)) {
                if (!tail) {
                    ret = node;
                } else {
                    tail->next = node;
                }
                tail = node;
            } else {
                return NULL;
            }
            p = p->next;
        }
        if (carry) {
            if (node = new ListNode(1)) {
                if (!tail) {
                    ret = node;
                } else {
                    tail->next = node;
                }
                tail = node;
            } else {
                return NULL;
            }
        }
        return ret;
    }
};
