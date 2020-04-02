/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
class Solution {
    class Record {
        Record (TreeNode node) {
            this.node = node;
            this.color = -1;
        }
        TreeNode node;
        int color;
    }
    public int pathSum(TreeNode root, int sum) {
        if (root == null) return 0;
        Record[] stack = new Record[1000];
        int top = 0;
        stack[0] = new Record(root);
        int count = 0;
        while (top >= 0) {
            Record topRecord = stack[top];
            if ((topRecord.color < 0) && (topRecord.node.left != null)) {
                topRecord.color = 0;
                stack[++top] = new Record(topRecord.node.left);
            } else if ((topRecord.color <= 0) && (topRecord.node.right != null)) {
                topRecord.color = 1;
                stack[++top] = new Record(topRecord.node.right);
            } else {
                for (int i = top, tsum = 0; i >= 0; i--) {
                    tsum += stack[i].node.val;
                    if (tsum == sum) count++;
                }
                top--;
            }
        }
        return count;
    }
}
