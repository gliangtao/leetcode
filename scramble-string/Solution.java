/**
Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty
substrings recursively.

Below is one possible representation of s1 = "great":

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t
To scramble the string, we may choose any non-leaf node and swap its two children.

For example, if we choose the node "gr" and swap its two children, it produces a scrambled string
"rgeat".

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t
We say that "rgeat" is a scrambled string of "great".

Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled
string "rgtae".

    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a
We say that "rgtae" is a scrambled string of "great".

Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.
*/

public class Solution {
    public static void main(String[] args) {
        System.out.format("isScramble(%s, %s): %b\n", args[0], args[1], new Solution().isScramble(args[0], args[1]));
    }

    /**
    //29ms version, DP, O(n^4)
    public boolean isScramble(String s1, String s2) {
        if ((s1 == null) || (s2 == null) || (s1.length() != s2.length())) return false;
        int len = s1.length();
        if (len == 0) return true;
        if (len == 1) return s1.equals(s2);
        int[][][] c = new int[len][len][len];
        int i, j, l;
        for (i = 0; i < len; i++) {
            for (j = 0; j < len; j++) {
                c[0][i][j] = (s1.charAt(i) == s2.charAt(j)) ? 1 : 0;
            }
        }
        for (l = 1; l < len; l++) {
            for (i = len - l - 1; i >= 0; i--) {
                for (j = len - l - 1; j >= 0; j--) {
                    int max, tmp, k;
                    max = 0;
                    for (k = l; k > 0; k--) {
                        tmp = c[k - 1][i][j] + c[l - k][i + k][j + k];
                        if (max < tmp) max = tmp;
                        tmp = c[k - 1][i][j + l - k + 1] + c[l - k][i + k][j];
                        if (max < tmp) max = tmp;
                    }
                    c[l][i][j] = max;
                }
            }
        }
        return (c[len - 1][0][0] == len);
    }
    */
    /**
    //27ms DP, O(n^4)
    public boolean isScramble(String s1, String s2) {
        if ((s1 == null) || (s2 == null) || (s1.length() != s2.length())) return false;
        int len = s1.length();
        if (len == 0) return true;
        if (len == 1) return s1.equals(s2);
        int i, j, l;

        int[] c1 = new int[26];
        int ch1, ch2, flags = 0;
        for (i = len - 1; i >= 0; i--) {
            ch1 = (int)(s1.charAt(i)) - 'a';
            ch2 = (int)(s2.charAt(i)) - 'a';
            if (ch1 != ch2) {
                if (c1[ch1] == 0) {
                    flags |= (1 << ch1);
                } else if (c1[ch1] == -1) {
                    flags &= ~(1 << ch1);
                }
                c1[ch1] += 1;
                if (c1[ch2] == 0) {
                    flags |= (1 << ch2);
                } else if (c1[ch2] == 1) {
                    flags &= ~(1 << ch2);
                }
                c1[ch2] -= 1;
            }
        }
        if (flags != 0) return false;

        int[][][] c = new int[len][len][len];
        for (i = 0; i < len; i++) {
            for (j = 0; j < len; j++) {
                c[0][i][j] = (s1.charAt(i) == s2.charAt(j)) ? 1 : 0;
            }
        }
        for (l = 1; l < len; l++) {
            for (i = len - l - 1; i >= 0; i--) {
                for (j = len - l - 1; j >= 0; j--) {
                    int max, tmp, k;
                    max = 0;
                    for (k = l; k > 0; k--) {
                        tmp = c[k - 1][i][j] + c[l - k][i + k][j + k];
                        if (max < tmp) max = tmp;
                        tmp = c[k - 1][i][j + l - k + 1] + c[l - k][i + k][j];
                        if (max < tmp) max = tmp;
                    }
                    c[l][i][j] = max;
                }
            }
        }
        return (c[len - 1][0][0] == len);
    }
    */

    //4ms, recursive version
    public boolean isScramble(String s1, String s2) {
        if ((s1 == null) || (s2 == null) || (s1.length() != s2.length())) return false;
        int[] c1 = new int[26];
        int i, flags = 0, len = s1.length();
        for (i = 0; i < len; i++) {
            int ch1 = (int)(s1.charAt(i)) - 'a';
            int ch2 = (int)(s2.charAt(i)) - 'a';
            if (ch1 != ch2) {
                if (c1[ch1] == 0) {
                    flags |= (1 << ch1);
                } else if (c1[ch1] == -1) {
                    flags &= ~(1 << ch1);
                }
                c1[ch1] += 1;
                if (c1[ch2] == 0) {
                    flags |= (1 << ch2);
                } else if (c1[ch2] == 1) {
                    flags &= ~(1 << ch2);
                }
                c1[ch2] -= 1;
            }
        }
        if (flags != 0) return false;   //False for different char set
        if (len <= 3) return true;      //True for any 1-2-3 len strings with same char set
        for (i = 1; i < len; i++) {
            if (isScramble(s1.substring(0, i), s2.substring(0, i)) &&
                isScramble(s1.substring(i), s2.substring(i))) {
                return true;
            }
            if (isScramble(s1.substring(0, i), s2.substring(len - i)) &&
                isScramble(s1.substring(i), s2.substring(0, len - i))) {
                return true;
            }
        }
        return false;
    }
}
