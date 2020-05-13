/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }

https://leetcode.com/problems/serialize-and-deserialize-binary-tree/

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

Example: 

You may serialize the following tree:

    1
   / \
  2   3
     / \
    4   5

as "[1,2,3,null,null,4,5]"
Clarification: The above format is the same as how LeetCode serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.
 * }
 */

//Pre-order search
public class Codec {
    // Encodes a tree to a single string.
    public String serialize(TreeNode root) {
        StringBuilder b = new StringBuilder();
        Stack<TreeNode> s = new Stack<TreeNode>();
        TreeNode node = root;
        while (!s.isEmpty() || (node != null)) {
            if (node != null) {
                b.append(node.val);
                b.append(",");
                s.push(node);
                node = node.left;
            } else {
                b.append("null,");
                node = s.pop();
                node = node.right;
            }
        }
        return b.toString();
    }
    // Decodes your encoded data to tree.
    public TreeNode deserialize(String data) {
        if ((data == null) || (data.isEmpty())) return null;
        String[] strs = data.split(",");
        if (strs.length == 0) return null;
        TreeNode root = new TreeNode(Integer.parseInt(strs[0]));
        int i = 1;
        Stack<TreeNode> st = new Stack<TreeNode>();
        TreeNode node = root;
        while (i < strs.length) {
            String str = strs[i];
            TreeNode next = "null".equals(str) ? null : new TreeNode(Integer.parseInt(str));
            if (node != null) {
                st.push(node);
                node = node.left = next;
            } else {
                node = st.pop();
                node = node.right = next;
            }
            i++;
        }
        return root;
    }
}
/** BFS
public class Codec {
    // Encodes a tree to a single string.
    public String serialize(TreeNode root) {
        if (root == null) return "";
        StringBuilder b = new StringBuilder();
        //LinkedList allows null
        LinkedList<TreeNode> q = new LinkedList<TreeNode>();
        q.offer(root);
        while (!q.isEmpty()) {
            TreeNode node = q.poll();
            if (node == null) {
                b.append("null,");
            } else {
                b.append(node.val);
                b.append(",");
                q.offer(node.left);
                q.offer(node.right);
            }
        }
        return b.toString();
    }
    // Decodes your encoded data to tree.
    public TreeNode deserialize(String data) {
        if ((data == null) || (data.isEmpty())) return null;
        String[] strs = data.split(",");
        if (strs.length == 0) return null;
        //ArrayDeque doesn't allow null
        ArrayDeque<TreeNode> nq = new ArrayDeque<TreeNode>();
        TreeNode root = new TreeNode(Integer.parseInt(strs[0]));
        nq.offer(root);
        int i = 1;
        while (i < strs.length) {
            TreeNode node = nq.poll();
            String left = strs[i++];
            if (!left.equals("null")) {
                node.left = new TreeNode(Integer.parseInt(left));
                nq.offer(node.left);
            }
            String right = strs[i++];
            if (!right.equals("null")) {
                node.right = new TreeNode(Integer.parseInt(right));
                nq.offer(node.right);
            }
        }
        return root;
    }
}
*/
