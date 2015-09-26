public class Solution {
    public int lengthOfLongestSubstring(String s) {
        if (s == null) {
            return 0;
        }
        char[] sa = s.toCharArray();
        int start = 0;
        int[] f = new int[256];
        int i;
        int end = sa.length;
        for (i = 255; i >= 0; i--) {
            f[i] = -1;
        }
        int ch;
        int len;
        int maxLen = -1;
        for (i = 0; i < end; i++) {
            ch = sa[i];
            if (f[ch] >= start) {
                len = i - start;
                if (maxLen < len) {
                    maxLen = len;
                }
                start = f[ch] + 1;
            }
            f[ch] = i;
        }
        len = i - start;
        if (maxLen < len) {
            maxLen = len;
        }
        return maxLen;
    }
}
