/**
Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.
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
    //1ms, one pointer, O(n)
    public ListNode deleteDuplicates(ListNode head) {
        ListNode dummy = new ListNode(Integer.MIN_VALUE);
        ListNode slow = dummy;
        while (head != null) {
            slow.next = head;
            head = head.next;
            while ((head != null) && (head.val == slow.next.val)) head = head.next;
            slow = slow.next;
            slow.next = null;
        }
        return dummy.next;
    }
}
