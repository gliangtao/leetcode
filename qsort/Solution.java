public class Solution {

    static int count = 0;
    private static void qsortImpl(int[] a, int start, int end) {
        count++;
        if (start < end) {
            final int mid = (end + start) / 2;
            final int x = a[mid];
            int i = start;
            for (int j = start; j < mid; j++) {
                if (a[j] <= x) {
                    int t = a[j];
                    a[j] = a[i];
                    a[i] = t;
                    i++;
                }
            }
            for (int j = mid + 1; j <= end; j++) {
                if (a[j] <= x) {
                    int t = a[j];
                    a[j] = a[i];
                    a[i] = t;
                    i++;
                }
            }
            a[mid] = a[i];
            a[i] = x;
            qsortImpl(a, start, i - 1);
            qsortImpl(a, i + 1, end);
        }
    }

    public static void qsort(int[] nums) {
        qsortImpl(nums, 0, nums.length - 1);
    }

    public static void main(String[] args) {
        int[] nums = new int[args.length];
        for (int i = 0; i < args.length; i++) {
            nums[i] = Integer.parseInt(args[i]);
        }
        qsort(nums);
        System.out.println("Result:");
        for (int i : nums) {
            System.out.print(i + ",　");
        }
        System.out.print("\n");
        System.out.println("count = " + count);
    }
}
