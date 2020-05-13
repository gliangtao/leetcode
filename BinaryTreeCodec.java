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
