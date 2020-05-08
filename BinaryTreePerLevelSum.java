/**
Binary tree per-Level sum: Level down when going left, level up when going right. Returns the list of sums of each level.

      1
    /   \
  2      3
 / \    / \
4   5  6   7

4,2,12=(1+5+6),3,7
*/
classs Solution {
    static class Node {
        int val;
        Node left;
        Node right;
    }
    
    public List<Integer> sumList(Node root) {
        Stack<Node> s = new Stack<Integer>();
        Node node = root;
        int level = 0;
        HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();
        while (!s.isEmpty() || (node != null)) {
            if (node != null) {
                s.push(node);
                int t = map.getOrDefault(level, 0) + node.val;
                map.put(level, t);
                node = node.left;
                level--;
            } else {
                node = s.pop();
                node = node.right;
                level++;
            }
        }
        List<Integer> ret = new ArrayList<Integer>(map.values());
        return ret;
    }
}
