/**
Given a sorted linked list, delete all nodes that have duplicate numbers,
leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.
*/

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
public class Solution {
    /*
    //1ms version
    public ListNode deleteDuplicates(ListNode head) {
        if (head == null) return null;
        int val;
        ListNode fakeNode = new ListNode(0);
        ListNode pn = fakeNode;
        boolean dup = false;
        pn.next = head;
        val = head.val;
        head = head.next;
        while (head != null) {
            if (val != head.val) {
                if (!dup) pn = pn.next;
                pn.next = head;
                val = head.val;
                dup = false;
            } else {
                dup = true;
            }
            head = head.next;
        }
        if (dup) pn.next = null;
        return fakeNode.next;
    }
    */

    //1ms version, two-pointers, O(n)
    public ListNode deleteDuplicates(ListNode head) {
        if (head == null) return null;
        ListNode dummy = new ListNode(0);
        ListNode slow, fast;
        slow = dummy;
        while (head != null) {
            fast = head.next;
            while ((fast != null) && (fast.val == head.val)) fast = fast.next;
            if (head.next == fast) {
                slow.next = head;
                slow = slow.next;
                slow.next = null;
            }
            head = fast;
        }
        return dummy.next;
    }
}
