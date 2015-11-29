/**
Given a linked list and a value x, partition it such that all nodes less than x come before nodes
greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.
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
    //1ms
    public ListNode partition(ListNode head, int x) {
        ListNode dummyLeft, dummyRight, left, right;
        dummyLeft = new ListNode(0);
        dummyRight = new ListNode(0);
        left = dummyLeft;
        right = dummyRight;
        while (head != null) {
            if (head.val < x) {
                left.next = head;
                left = head;
            } else {
                right.next = head;
                right = head;
            }
            head = head.next;
        }
        right.next = null;
        left.next = dummyRight.next;
        return dummyLeft.next;
    }
}

