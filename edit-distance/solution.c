
#include <stdlib.h>
#include <limits.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>
#ifdef MY_UNIT_TEST
#define DBG(str...) printf(str)
#define bool    int
#define true    1
#define false   0

int minDistance(char* word1, char* word2);

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int ret;
    int retSize;
    gettimeofday(&tvStart, NULL);
    ret = minDistance(argv[1], argv[2]);
    gettimeofday(&tvEnd, NULL);

    printf("minDistance('%s', '%s'): %d\n", argv[1], argv[2], ret);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, minDistance\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif

/*
Given two words word1 and word2, find the minimum number of steps required to convert word1 to
word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character
*/

static void getPi(char* p, int* pi, int n) {
    int i, k;
    k = 0;
    for (i = 1; i < n; i++) {
        while ((k > 0) && (p[i] != p[k])) k = pi[k - 1];
        if (p[i] == p[k]) {
            k++;
        }
        pi[i] = k;
    }
}

static int maxMatch(char* s, char* p, int* pi, int n, int* pos) {
    int k = 0;
    int ch;
    int max = 0;
    int oPos = *pos;
    if (oPos >= n) return -1;
    char* q = s + oPos;
    while ((ch = *q++) != '\0') {
        while ((k > 0) && (ch != p[k])) k = pi[k - 1];
        if (ch == p[k]) {
            k++;
            if (k == n) {
                *pos = (int)(q - s);
                return n;
            }
            if (max < k) {
                *pos = (int)(q - s);
                max = k;
            }
        }
    }
    return max;
}

#if 0
#define MY_MAX(a,b) (((a) < (b)) ? (b) : (a))

int minDistance(char* word1, char* word2) {
    int len1, len2;
    len1 = (!word1 || !(*word1)) ? 0 : strlen(word1);
    len2 = (!word2 || !(*word2)) ? 0 : strlen(word2);

    if (!len1) return len2;
    if (!len2) return len1;

    int alen, blen;
    char* a, *b;
    if (len1 <= len2) {
        alen = len1;
        blen = len2;
        a = word1;
        b = word2;
    } else {
        alen = len2;
        blen = len1;
        a = word2;
        b = word1;
    }

    //Now alen <= bLen
    //Look for longest common substring
    const int ALEN = alen;
    int pi[ALEN];
    
    pi[0] = 0;
    int i, k, minVal = blen, val, pos;
    for (i = 0; i < ALEN; i++) {
        getPi(a + i, pi, ALEN - i);
        pos = 0;
        while ((k = maxMatch(b, a + i, pi, ALEN - i, &pos)) > 0) {
            //a: [a+i, a+i+k]
            //b: [pos - k, pos]
            val = MY_MAX(i, pos - k) + MY_MAX(ALEN - i - k, blen - pos);
            if (minVal > val) minVal = val;
        }
    }
    if (minVal > blen - alen) {
        int finalDiffs = 0;
        char* p;
        int ch;
        int d;
        int ac[26];
        int bc[26];
        for (i = 0; i < 26; i++) ac[i] = bc[i] = 0;
        for (p = a; (ch = *p) != 0; p++) {
            ac[ch - 'a'] += 1;
        }
        for (p = b; (ch = *p) != 0; p++) {
            bc[ch - 'a'] += 1;
        }
        for (i = 0; i < 26; i++) {
            d = bc[i] - ac[i];
            if (d < 0) d = -d;
            finalDiffs += ((d < 0) ? (-d) : d);
        }
        minVal = ((finalDiffs + minVal) >> 1);
    }
    return minVal;
}

#endif
#if 0
typedef struct {
    int d;
    int match;
    int start;
    int end;
} MyNode;

static int myfindchr(char* p, int chr, MyNode* node) {
    char* q = p + node->start;
    char* endp = p + node->end;
    while (q <= endp) {
        if (*q == chr) {
            return (int)(q - p);
        }
        q++;
    }
    return -1;
}

static int firstChrAfter(char* p, int ch, int start, int nulPos) {
    for (int i = start + 1; i < nulPos; i++) {
        if (p[i] == ch) return i;
    }
    return nulPos;
}

static int lastChrBefore(char* p, int ch, int end) {
    for (int i = end - 1; i >= 0; i--) {
        if (p[i] == ch) return i;
    }
    return -1;
}

int minDistance(char* word1, char* word2) {
    int len1, len2;
    len1 = (!word1 || !(*word1)) ? 0 : strlen(word1);
    len2 = (!word2 || !(*word2)) ? 0 : strlen(word2);

    if (!len1) return len2;
    if (!len2) return len1;

    int alen, blen;
    char* a, *b;
    if (len1 <= len2) {
        alen = len1;
        blen = len2;
        a = word1;
        b = word2;
    } else {
        alen = len2;
        blen = len1;
        a = word2;
        b = word1;
    }

    //Now alen <= bLen
    const int ALEN = alen;
    MyNode c[ALEN + 1][2];
    int i, l, d1, d2, toggle = 0;

    for (i = 0; i <= ALEN; i++) {
        c[i][0].d = blen + alen;
        c[i][0].start = -1;
        c[i][0].end = ALEN;
    }

    for (l = 1; l <= ALEN; l++) {
        for (i = 0; i <= ALEN - l; i++) {
            int start, end, d1, d2, match1, match2;
            breakme();
            //(i, c[i][l-1]), (c[i+1][l-1], i + l - 1)
            //c[i][l].start >= c[i + 1][l - 1].start
            //c[i][l].end <= c[i + 1][l - 1].end

            //a[i] <-> b[end]
            end     = lastChrBefore(b, a[i], c[i + 1][toggle].end);
            //a[i + l - 1] <-> b[start]
            start   = firstChrAfter(b, a[i + l - 1], c[i][toggle].start, blen);
            d1      = c[i][toggle].d - ((start < blen) << 1);
            d2      = c[i + 1][toggle].d - ((end >= 0) << 1);
            
            if (start < blen) {
                match1 = c[i][toggle].match + 1;
                d1 = c[i][toggle].d - 1;
            }
            if (end >= 0) {
                match2 = c[i+1][toggle].match + 1;
                d2 = 
            }
            c[i][!toggle].start = start;
            c[i][!toggle].end = end;
            if (d1 < d2) {
                c[i][!toggle].d = d1;
                c[i][!toggle].match = match1;
            } else {
                c[i][!toggle].d = d2;
                c[i][!toggle].match = match2;
            }
            printf("c[i %d][cur %d]: start %d, end %d, d %d\n", i, !toggle,
                start, end, c[i][!toggle].d);
        }
        toggle = !toggle;
    }
    return c[0][toggle].d;
}
#endif




#if 0
int minDistance(char* word1, char* word2) {
    int len1, len2;
    len1 = (!word1 || !(*word1)) ? 0 : strlen(word1);
    len2 = (!word2 || !(*word2)) ? 0 : strlen(word2);

    int alen, blen;
    char* a, *b;
    if (len1 <= len2) {
        alen = len1;
        blen = len2;
        a = word1;
        b = word2;
    } else {
        alen = len2;
        blen = len1;
        a = word2;
        b = word1;
    }

    if (!alen) return blen;

    //Now alen <= bLen
    //Look for longest common substring
    const int ALEN = alen;
    const int DLEN = alen + blen;
    int d[DLEN];
    int i;

    for (i = 0; i < ALEN; i++) d[i] = i;
    for (; i <= blen; i++) d[i] = ALEN;
    for (; i < DLEN; i++) d[i] = DLEN - i;

    #ifdef MY_UNIT_TEST
    printf("1. D[%d]: ", DLEN);
    for (i = 0; i < DLEN; i++) printf(",%d", d[i]);
    printf("\n");
    #endif

    for (i = 0; i < ALEN; i++) {
        char* p = a + i;
        char* q = b - 1;
        int ch;
        int chi = *p;
        while ((ch = *(++q)) != '\0') {
            if (ch == chi) {
                // b[q - b] <-> a[i]
                // (q - b) + ALEN == i + d_index
                // d_index = ALEN + (q - b) - i
                int d_index = ALEN + (q - b) - i;
                d[d_index] += 1;
                #ifdef MY_UNIT_TEST
                printf("1. i %d, d[%d] += 1 -> %d\n", i, d_index, d[d_index]);
                #endif
            }
        }
    }

    #ifdef MY_UNIT_TEST
    printf("2. D[%d]: ", DLEN);
    for (i = 0; i < DLEN; i++) printf(",%d", d[i]);
    printf("\n");
    #endif

    int maxVal = alen;
    for (i = 0; i < DLEN; i++) {
        if (d[i] > maxVal) maxVal = d[i];
    }

    return DLEN - maxVal;
}

#endif


#if 0
int minDistance(char* word1, char* word2) {
    int len1, len2;
    len1 = (!word1 || !(*word1)) ? 0 : strlen(word1);
    len2 = (!word2 || !(*word2)) ? 0 : strlen(word2);

    int alen, blen;
    char* a, *b;
    if (len1 <= len2) {
        alen = len1;
        blen = len2;
        a = word1;
        b = word2;
    } else {
        alen = len2;
        blen = len1;
        a = word2;
        b = word1;
    }

    if (!alen) return blen;

    //Now alen <= bLen
    //Look for longest common substring
    const int ALEN = alen;
    const int BLEN = blen;
    int c[ALEN][BLEN];
    int d[ALEN][BLEN];
    int al, bl, i, j;

    memset(c, 0, sizeof(int) * ALEN * BLEN);
    memset(d, 0, sizeof(int) * ALEN * BLEN);

    for (al = 1; al <= ALEN; al++) {
        for (i = 0; i <= ALEN - al; i++) {
            for (bl = 1; bl <= BLEN; bl++) {
                for (j = 0; j <= BLEN - bl; j++) {
                    #ifdef MY_UNIT_TEST
                    if (!i && !j)
                    printf("c[%d][%d][%d][%d] %d -> %d, a '%c' b '%c'\n",
                        i, j, al, bl,
                        c[i][j], c[i][j] + !(a[i + al - 1] != b[j + bl - 1]),
                        a[i + al - 1], b[j + bl - 1]);
                    #endif
                    if (!(a[i + al - 1] != b[j + bl - 1])) {
                        c[i][j] += 1;
                        if (!d[i][j]) {
                            if (1) {
                                //a[i + al - 1] == b[j + bl - 1]
                                // min(i + al - 1, j + bl - 1) + min(ALEN - i - al + 1, BLEN - j - bl + 1)
                                int v1 = i + al - 1;
                                int v2 = j + bl - 1;
                                int v3 = ALEN - v1;
                                int v4 = BLEN - v2;
                                d[i][j] = ((v1 < v2) ? (v1) : (v2)) + ((v3 < v4) ? (v3) : (v4));
                            }
                        }
                    }
                }
            }
        }
    }
    #ifdef MY_UNIT_TEST
    printf("c[%d][%d]:\n", ALEN, BLEN);
    for (i = 0; i < ALEN; i++) {
        printf("%3d: [%3d", i, c[i][0]);
        for (j = 1; j < BLEN; j++) {
            printf(",%3d", c[i][j]);
        }
        printf("]\n");
    }
    printf("d[%d][%d]:\n", ALEN, BLEN);
    for (i = 0; i < ALEN; i++) {
        printf("%3d: [%3d", i, d[i][0]);
        for (j = 1; j < BLEN; j++) {
            printf(",%3d", d[i][j]);
        }
        printf("]\n");
    }
    #endif
    int result = (ALEN + BLEN - c[0][0] - d[0][0]);
    return result;
}
#endif

#if 0
int minDistance(char* word1, char* word2) {
    int s1 = strlen(word1);
    int s2 = strlen(word2);
    if (s1 == 0 || s2 == 0) return s1 + s2;
    int ret[s2];
    int i,j,p,q,s,t,u;
    for (j = 0; j < s2; ++j) ret[j] = j+1; // n of steps to go from empty string to word2[:j]
    for (i =0; i < s1; ++i){
        char c1 = word1[i];
        for (j =0; j < s2; ++j) {
            char c2 = word2[j];
            q = ret[j]; // save the ret[j-1] from previous i iteration for the next j iteration
            if (c1 == c2) ret[j] = (j==0) ? i : p; // if 2nd str has a single char, n steps = len(1st str) - 1, since last chars cancel
            else{ // find min of three possible previous dp steps: (i-1,j), (i,j-1), and (i-1,j-1), each + 1
                u = ret[j-1];
                s = ( (j==0) ? i: (u > p ? p : u ) ) ; 
                t = ret[j];
                ret[j] = ( s > t ? t : s ) + 1;
            }
            p = q; 
        }
    }
    return ret[s2-1];
}

#endif

#if 0
//12ms version, DP, O(mXn) space, O(mXn) time
int minDistance(char* word1, char* word2) {
    const int ALEN = (!word1 || !(*word1)) ? 0 : strlen(word1);
    const int BLEN = (!word2 || !(*word2)) ? 0 : strlen(word2);

    int c[ALEN + 1][BLEN + 1];
    int i, j;

    for (i = 0; i <= ALEN; i++) c[i][0] = i;
    for (j = 1; j <= BLEN; j++) c[0][j] = j;
    for (i = 1; i <= ALEN; i++) {
        int ch = word1[i - 1];
        for (j = 1; j <= BLEN; j++) {
            int v, v1, v2;
            v = c[i - 1][j - 1] + (ch != word2[j - 1]);
            v1 = (c[i - 1][j] + 1);
            if (v > v1) v = v1;
            v2 = (c[i][j - 1] + 1);
            if (v > v2) v = v2;
            c[i][j] = v;
        }
    }

    #ifdef MY_UNIT_TEST
    printf("c[%d][%d]:\n", ALEN + 1, BLEN + 1);
    printf("      %3d", 0);
    for (j = 1; j <= BLEN; j++) {
        printf(" %3d", j);
    }
    printf("\n");
    for (i = 0; i <= ALEN; i++) {
        printf("%3d: [%3d", i, c[i][0]);
        for (j = 1; j <= BLEN; j++) {
            printf(",%3d", c[i][j]);
        }
        printf("]\n");
    }
    #endif
    return c[ALEN][BLEN];
}
#endif

int minDistance(char* word1, char* word2) {
    const int ALEN = (!word1 || !(*word1)) ? 0 : strlen(word1);
    const int BLEN = (!word2 || !(*word2)) ? 0 : strlen(word2);

    int c[ALEN + 1][2];
    int i, j;

    for (i = 0; i <= ALEN; i++) c[i][0] = i;

    int cur = 0, v;
    for (j = 1; j <= BLEN; j++) {
        int ch = word2[j - 1];
        cur = !cur;
        c[0][cur] = j;
        for (i = 1; i <= ALEN; i++) {
            v = c[i - 1][!cur] + (word1[i - 1] != ch);
            if (v > c[i - 1][cur] + 1) v = c[i - 1][cur] + 1;
            if (v > c[i][!cur] + 1) v = c[i][!cur] + 1;
            c[i][cur] = v;
        }
    }

    #ifdef MY_UNIT_TEST
    printf("c[%d]: [%3d", ALEN + 1, c[0][cur]);
    for (i = 1; i <= ALEN; i++) {
        printf(",%3d", c[i][cur]);
    }
    printf("]\n");
    #endif
    return c[ALEN][cur];
}

