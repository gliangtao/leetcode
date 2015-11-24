
public class BinaryTree<T extends Comparable<T>> {
    private Node<T> root;
    private int maxHeight;
    private static class Node<T extends Comparable<T>> {
        public Node(T val) {
            this.val = val;
        }
        public Node() {
        }
        T       val;
        Node<T> left;
        Node<T> right;
    }

    public void add(T val) {
        Node<T> node = new Node<>(val);
        if (root == null) {
            root = node;
            maxHeight = 1;
            return;
        }
        Node<T> p = root;
        Node<T> prev = root;
        int d = 0;
        int height = 1;
        while (p != null ) {
            prev = p;
            d = val.compareTo(p.val);
            if (d == 0) return;
            if (d < 0) {
                p = p.left;
            } else {
                p = p.right;
            }
            height++;
        }
        if (d == 0) return;
        if (d < 0) {
            prev.left = node;
        } else {
            prev.right = node;
        }
        if (height > maxHeight) maxHeight = height;
    }

    public void print() {
        if (root != null) {
            @SuppressWarnings({"unchecked"}) Node<T>[] s = (Node<T>[]) new Node[maxHeight];
            Node<T> p;
            int top = 0;
            s[top] = root;
            while (top >= 0) {
                p = s[top].left;
                while (p != null) {
                    s[++top] = p;
                    p = p.left;
                }
                p = s[top];
                System.out.format("%s\n", p.val.toString());
                if (p.right == null) {
                    while ((top > 0) && (s[top] == s[top - 1].right)) top--;
                    top--;
                    if (top < 0) return;
                    System.out.format("%s\n", s[top].val.toString());
                    if (s[top].right == null) return;
                }
                s[top + 1] = s[top].right;
                top++;
            }
        }
    }

    public static void test0() {
        // Instantiate the tree
        BinaryTree<Integer> tree = new BinaryTree<Integer>();

        // Print its content (in ascending order)
        tree.print();
        // Should print nothing
    }

    public static void test1() {
        // Instantiate the tree
        BinaryTree<Integer> tree = new BinaryTree<Integer>();

        tree.add(10);
        tree.add(2);
        tree.add(5);
        tree.add(4);
        tree.add(8);
        tree.add(20);
        tree.add(9);

        // Print its content (in ascending order)
        tree.print();

        // Should print:
        // 2
        // 4
        // 5
        // 8
        // 9
        // 10
        // 20
    }

    public static void test2() {
        // Instantiate the tree
        BinaryTree<Float> tree = new BinaryTree<Float>();

        // Add elements
        tree.add(5.0f);
        tree.add(1.1f);
        tree.add(1.0f);
        tree.add(3.2f);
        // Print its content (in ascending order)
        tree.print();


        // Should print:
        // 1.0
        // 1.1
        // 3.2
        // 5.0
    }

    public static void main(String[] args) {
        test0();
        test1();
        test2();
    }
}

/*
public class Test {
    private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
    private final ByteArrayOutputStream errContent = new ByteArrayOutputStream();

    @Before
    public void setUpStreams() {
        System.setOut(new PrintStream(outContent));
        System.setErr(new PrintStream(errContent));
    }

    @After
    public void cleanUpStreams() {
        System.setOut(null);
        System.setErr(null);
    }

    @org.junit.Test
    public void test0() {
        // Instantiate the tree
        BinaryTree<Integer> tree = new BinaryTree<Integer>();

        // Print its content (in ascending order)
        tree.print();
        // Should print nothing
        assertEquals((outContent.toString() == null) || (outContent.toString().isEmpty()));
    }

    @org.junit.Test
    public void test1() {
        // Instantiate the tree
        BinaryTree<c> tree = new BinaryTree<Integer>();

        tree.add(10);
        tree.add(2);
        tree.add(5);
        tree.add(4);
        tree.add(8);
        tree.add(20);
        tree.add(9);

        // Print its content (in ascending order)
        tree.print();

        assertEquals("2\n4\n5\n8\n9\n10\n20\n", outContent.toString());
        // Should print:
        // 2
        // 4
        // 5
        // 8
        // 9
        // 10
        // 20
    }

    @org.junit.Test
    public void test2() {
        // Instantiate the tree
        BinaryTree<Float> tree = new BinaryTree<Float>();

        // Add elements
        tree.add(5.0f);
        tree.add(1.1f);
        tree.add(1.0f);
        tree.add(3.2f);
        // Print its content (in ascending order)
        tree.print();

        assertEquals("1.0\n1.1\n3.2\n5.0\n", outContent.toString());

        // Should print:
        // 1.0
        // 1.1
        // 3.2
        // 5.0
    }
}
*/
