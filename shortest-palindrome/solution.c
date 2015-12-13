/**
Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it.
Find and return the shortest palindrome you can find by performing this transformation.

For example:

Given "aacecaaa", return "aaacecaaa".

Given "abcd", return "dcbabcd".
*/


#ifdef MY_UNIT_TEST
#define DBG(str...) printf(str)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char* shortestPalindrome(char* s);
int main(int argc, char** argv) {
    char* ret = shortestPalindrome(argv[1]);
    if (ret != NULL) {
        printf("Shortest Palindrome for '%s':\n'%s'\n", argv[1], ret);
    }
    free(ret);
    return 0;
}
#else
#define DBG(str...)
#endif

//0ms, O(n), KMP
char* shortestPalindrome(char* s) {
    if (!s || !*s) return strdup("");
    const int N = strlen(s);
    const int HN = (N >> 1);
    int pi[HN], k, i, ch;

    // Get prefix array
    k = pi[0] = 0;
    for (i = 1; i < HN; i++) {
        ch = s[i];
        while ((k > 0) && (ch != s[k])) k = pi[k - 1];
        if (ch == s[k]) k++;
        pi[i] = k;
    }

    // Match in reverse order
    for (i = N - 1, k = 0; i >= k; i--) {
        ch = s[i];
        while ((k > 0) && (ch != s[k])) k = pi[k - 1];
        if (ch == s[k]) k++;
    }

    // Finally, only (N - i - k - 1) chars need to be added to make the shortest palindrome
    int len = N - (i + k);
    char* ret = (char*)malloc((len + N)* sizeof(char));
    if (ret != NULL) {
        char* p = ret;
        for (i = N - 1; i > N - len; i--) *p++ = s[i];
        strcpy(p, s);
    }

    return ret;
}
