/**
Given a string S and a string T, count the number of distinct subsequences of T in S.

A subsequence of a string is a new string which is formed from the original string by deleting some
(can be none) of the characters without disturbing the relative positions of the remaining
characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Here is an example:
S = "rabbbit", T = "rabbit"

Return 3.
*/
#if 0
//4ms
int numDistinct(char* s, char* t) {
    if (!s || !t) return 0;
    const int NS = strlen(s);
    const int NT = strlen(t);
    if (NS < NT) return 0;
    if (NS == NT) return !strcmp(s, t);

    int c[NS][NT];
    int i, j, k, chs, cht;
    c[0][0] = (s[0] == t[0]);
    for (i = 1; i < NS; i++) c[i][0] = (s[i] == t[0]) + c[i - 1][0];
    for (j = 1; j < NT; j++) c[0][j] = 0;
    for (j = 1; j < NT; j++) {
        cht = t[j];
        for (i = 1; i < NS; i++) {
            if (s[i] == cht) {
                c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
            } else {
                c[i][j] = c[i - 1][j];
            }
        }
    }
    return c[NS - 1][NT - 1];
}
#endif

//0ms
int numDistinct(char* s, char* t) {
    if (!s || !t) return 0;
    const int NS = strlen(s);
    const int NT = strlen(t);
    if (NS < NT) return 0;
    if (NS == NT) return !strcmp(s, t);
    if (!NT) return 0;

    int c[NT];
    int i, j, chs, limit;
    for (j = 0; j < NT; j++) c[j] = 0;
    for (i = 0; i < NS; i++) {
        chs = s[i];
        limit = NT - 1;
        if (limit > i) limit = i;
        for (j = limit; j > 0; j--) {
            if (t[j] == chs) c[j] += c[j - 1];
        }
        if (t[0] == chs) c[0]++;
    }
    return c[NT - 1];
}
