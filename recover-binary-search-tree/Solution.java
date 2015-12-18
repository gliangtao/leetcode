/**
Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?
confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.


OJ's Binary Tree Serialization:
The serialization of a binary tree follows a level order traversal, where '#' signifies a path
terminator where no node exists below.

Here's an example:
   1
  / \
 2   3
    /
   4
    \
     5
The above binary tree is serialized as "{1,2,3,#,#,4,#,#,5}".
*/

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
//NOT Finished.
public class Solution {
    /**
    public void recoverTree(TreeNode root) {
        if (root == null) return;
        int tval = 0;
        TreeNode min = new TreeNode(Integer.MAX_VALUE);
        TreeNode max = new TreeNode(Integer.MIN_VALUE);
        TreeNode left, right, node;
        Stack<TreeNode> s = new Stack<>();
        node = root;
        while (true) {
            if (node != null) {
                left = node.left;
                if ((left != null) && (left.val > node.val)) {
                    if (min.val > node.val) min = node;
                    if (max.val < left.val) max = left;
                    //if ((max.val <= 3) && (min.val >= 0))
                    //System.out.format("min %d, max %d\n", min.val, max.val);
                }
                s.push(node);
                node = left;
            } else if (!s.empty()) {
                node = s.pop();
                right = node.right;
                if ((right != null) && (right.val < node.val)) {
                    if (min.val > right.val) min = right;
                    if (max.val < node.val) max = node;
                    //if ((max.val <= 3) && (min.val >= 0))
                    //System.out.format("min %d, max %d\n", min.val, max.val);
                }
                node = right;
            } else {
                break;
            }
        }
        tval = min.val;
        min.val = max.val;
        max.val = tval;
    }
    */
    public void recoverTree(TreeNode root) {
        if (root == null) return;
        int tval;
        TreeNode min = new TreeNode(Integer.MAX_VALUE);
        TreeNode max = new TreeNode(Integer.MIN_VALUE);
        TreeNode left, right, node;
        Stack<TreeNode> s = new Stack<>();
        node = root;
        while (true) {
            if (node != null) {
                left = node.left;
                if ((left != null) && (left.val > node.val)) {
                    if (min.val > node.val) min = node;
                    if (max.val < left.val) max = left;
                    //if ((max.val <= 3) && (min.val >= 0))
                    //System.out.format("min %d, max %d\n", min.val, max.val);
                }
                s.push(node);
                node = left;
            } else if (!s.empty()) {
                node = s.pop();
                right = node.right;
                if ((right != null) && (right.val < node.val)) {
                    if (min.val > right.val) min = right;
                    if (max.val < node.val) max = node;
                    //if ((max.val <= 3) && (min.val >= 0))
                    //System.out.format("min %d, max %d\n", min.val, max.val);
                }
                node = right;
            } else {
                break;
            }
        }
        tval = min.val;
        min.val = max.val;
        max.val = tval;
    }
}
