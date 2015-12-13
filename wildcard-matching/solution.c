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

char* multiply(char* num1, char* num2);
bool isMatch(char* s, char* p);

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    bool ret;
    gettimeofday(&tvStart, NULL);
    ret = isMatch(argv[1], argv[2]);
    gettimeofday(&tvEnd, NULL);

    printf("isMatch('%s', '%s'): %s\n", argv[1], argv[2], ret ? "true" : "false");
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    DBG("Time %d.%06d, isMatch\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif
/*
Implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "*") → true
isMatch("aa", "a*") → true
isMatch("ab", "?*") → true
isMatch("aab", "c*a*b") → false
*/
#include <sys/types.h>
#include <limits.h>

#if 0
//this version gets "true" for "aab" <-> "c*a*b". Not matching the requirement.
bool isMatch(char* s, char* p) {
    if (!s || !p) {
        return (s == p);
    }

    DBG("Calling isMatch('%s', '%s')\n", s, p);

    if ((*p == '*') && (p[1] == 0)) return true;
    if (!strcmp(p, "?*")) return (*s != 0);

    char *q, *r;

    q = s;
    r = p;
    while (*q && (((*r == *q) || (*r == '?')) && (r[1] != '*'))) { q++; r++; }
    if (*r == 0) return (*q == 0);
    if (*q == 0) {
        while (*r != 0) {
            if (r[1] == '*') r += 2;
            else if (*r == '*') r++;
            else return false;
        }
        return true;
    }

    if (r[1] != '*') return false; //FIXME: what if *r == '*' ?

    int ch;
    if (*r == '?') {
        r += 2;
        while (*r != 0) {
            if (r[1] == '*') r+= 2;
            else break;
        }
        ch = *r;
        for (q--; (q = strchr(q + 1, ch)) != NULL;) {
            if (isMatch(q, r)) return true;
        }
    } else {
        ch = *r;
        r += 2;
        do {
            if (isMatch(q, r)) return true;
        } while (*q++ == ch);
    }
    return false;
}
#endif

#if 0
//This version timeout
bool isMatch(char* s, char* p) {
    if (!s || !p) {
        return (s == p);
    }

    DBG("Calling isMatch('%s', '%s')\n", s, p);

    if ((*p == '*') && (p[1] == 0)) return true;
    if (!strcmp(p, "?*")) return (*s != 0);

    char *q, *r;

    q = s;
    r = p;
    while (*q && ((*r == '?') || ((*r == *q) && (*r != '*')))) { q++; r++; }
    if (*r == 0) return (*q == 0);
    if (*q == 0) {
        while (*r != 0) {
            if (*r == '*') r++;
            else return false;
        }
        return true;
    }

    //(*r == *q) && (*r != '*') == false, AND (*r != '?')
    // Either (*r != *q), or (*r == '*')
    if (*r != '*') return false; // Note: *r != '?'

    while (*(++r) == '*');
    int ch = *r;
    for (q--; (q = strchr(q + 1, ch)) != NULL;) {
        if (isMatch(q, r)) return true;
    }
    return false;
}
#endif

#if 0
//80ms version, O(m*n) time, O(n) memory
bool isMatch(char* s, char* p) {
    if (!s || !p) {
        return (s == p);
    }

    const int N = strlen(s);
    int c[N + 1];
    memset(c, 0, sizeof(c));

    c[0] = 1;

    char* r = p;
    int ch, i;

    while ((ch = *r++)) {
        if (ch == '*') {
            for (i = 1; i <= N; i++) {
                if (c[i - 1] && !c[i]) c[i] = 1;
            }
        } else {
            for (i = N; i > 0; i--) {
                c[i] = c[i - 1] && ((ch == s[i - 1]) || (ch == '?'));
            }
            c[0] = 0;
        }
    }
    return c[N];
}
#endif

#if 0
//80ms version, O(m*n) time, O(n) memory
bool isMatch(char* s, char* p) {
    if (!s || !p) {
        return (s == p);
    }

    const int N = strlen(s);
    int c[N + 1];
    memset(c, 0, sizeof(c));

    c[0] = 1;

    char* r = p;
    int ch, i;

    while ((ch = *r++)) {
        if (ch == '*') {
            for (i = 1; i <= N; i++) {
                if (c[i - 1] && !c[i]) c[i] = 1;
            }
        } else {
            if (ch == '?') {
                for (i = N; i > 0; i--) {
                    c[i] = c[i - 1];
                }
            } else {
                for (i = N; i > 0; i--) {
                    c[i] = c[i - 1] && (ch == s[i-1]);
                }
            }
            c[0] = 0;
        }
    }
    return c[N];
}
#endif

#if 0
//76ms
bool isMatch(char* s, char* p) {
    if (!s || !p) {
        return (s == p);
    }

    const int N = strlen(s);
    int c[N + 1];
    memset(c, 0, sizeof(c));

    c[0] = 1;

    char* r;
    int ch, i;

    while ((ch = *p++)) {
        if (ch == '*') {
            while (*p++ == '*');
            p--;
        }
        if (ch == '*') {
            for (i = 1; i <= N; i++) {
                if (c[i - 1] && !c[i]) c[i] = 1;
            }
        } else {
            if (ch == '?') {
                for (i = N; i > 0; i--) {
                    c[i] = c[i - 1];
                }
            } else {
                for (i = N; i > 0; i--) {
                    c[i] = c[i - 1] && (ch == s[i-1]);
                }
            }
            c[0] = 0;
        }
    }
    return c[N];
}
#endif

#if 0
//8ms, https://leetcode.com/discuss/10133/linear-runtime-and-constant-space-solution
//Could be wrong, though passing test
bool isMatch(const char *s, const char *p) {
    const char* star=NULL;
    const char* ss=s;
    while (*s){
        //advancing both pointers when (both characters match) or ('?' found in pattern)
        //note that *p will not advance beyond its length
        if ((*p=='?')||(*p==*s)){s++;p++;continue;}

        // * found in pattern, track index of *, only advancing pattern pointer
        if (*p=='*'){star=p++; ss=s;continue;}

        //current characters didn't match, last pattern pointer was *, current pattern pointer is not *
        //only advancing pattern pointer
        if (star){ p = star+1; s=++ss;continue;}

       //current pattern pointer is not star, last patter pointer was not *
       //characters do not match
        return false;
    }

   //check for remaining characters in pattern
    while (*p=='*'){p++;}

    return !*p;
}
#endif

#if 0
//A KMP solution, which should work - not implemented or tested
//Split "p" into sub-strings separated by "*", KMP-match each substring one-by-one.
// Time should be O(m + n), space should be O(m). Simply use "strStr" to skip "*" matched substrs
static void getPi(char*p, int* pi, int n) {
    int i, k, ch;
    k = pi[0] = 0;

    for (i = 1; i < n; i++) {
        ch = p[i];
        while ((k > 0) && (ch != p[k]) && (ch !='?')) k = pi[k - 1];
        if ((ch == p[k]) || (p[k] == '?')) k++;
        pi[i] = k;
    }
}

static char* kmpStrstr(char* s, char* p, int* pi, int n) {
    int i, k, ch;
    k = pi[0] = 0;
    memset(pi, 0, n * sizeof(int));
    getPi(p, pi, n);

    for (i = 0; (ch = s[i]) != 0; i++) {
        while ((k > 0) && (ch != p[k]) && (p[k] !='?')) k = pi[k - 1];
        if ((ch == p[k]) || (p[k] == '?')) {
            k++;
            if (k == n) return s + i + 1;
        }
    }
    return NULL;
}

static char* myStrchrnul(char* p, int ch) {
    int c;
    while ((c = *p) && (c != ch)) p++;
    return p;
}

//12ms version
bool isMatch(char* s, char* p) {
    char* q;
    const int PLEN = strlen(p);
    int pi[PLEN];
    int initial = 1;
    while (p && *p) {
        q = strchr(p, '*');
        if (q != NULL) {
            if (initial) {
                initial = 0;
                int slen = strlen(s);
                if (slen < q - p) return false;
                for (int i = 0; i < q - p; i++) {
                    if ((s[i] != p[i]) && (p[i] != '?')) return false;
                }
                //printf("kmpStrstr(s %s, p %s): %s, q - p %ld\n", s, p, s + (q - p), q - p);
                s += q - p;
            } else {
                s = kmpStrstr(s, p, pi, q - p);
                //printf("kmpStrstr(p %s): %s\n", p, s);
                if (!s) return false;
            }
            while (*q == '*') q++;
            if (*q == 0) return true;
        } else {
            int plen = strlen(p);
            int slen = strlen(s);
            if (plen <= slen) {
                if (initial && (plen != slen)) return false;
                s += slen - plen;
                for (int i = 0; i < plen; i++) {
                    if ((s[i] != p[i]) && (p[i] != '?')) return false;
                }
                return true;
            }
            return false;
        }
        p = q;
    }
    return (*s == 0);
}
#endif

#if 0
//12ms
bool isMatch(char* s, char* p) {
    const int SLEN = strlen(s);
    const int PLEN = strlen(p);
    int si, pi, si_saved = -1, pi_saved, chs, chp;
    for (si = 0, pi = 0; si < SLEN;) {
        if (pi >= PLEN) {
            if (si_saved >= 0) {
                si = ++si_saved;
                pi = pi_saved;
                continue;
            }
            return false;
        }
        chs = s[si];
        chp = p[pi];
        if (chp == '*') {
            si_saved = si;
            pi_saved = ++pi;
        } else {
            if ((chs == chp) || (chp == '?')) {
                si++;
                pi++;
            } else if (si_saved >= 0) {
                si = ++si_saved;
                pi = pi_saved;
            } else {
                return false;
            }
        }
    }
    for (; pi < PLEN; pi++) {
        if (p[pi] != '*') return false;
    }
    return true;
}
#endif

//8ms
bool isMatch(char* s, char* p) {
    char *ss = NULL, *sp;
    int chs, chp;
    while ((chs = *s) != 0) {
        chp = *p;
        if (chp == '*') {
            ss = s;
            sp = ++p;
        } else if ((chs == chp) || (chp == '?')) {
            s++;
            p++;
        } else if (ss != NULL) {
            s = ++ss;
            p = sp;
        } else {
            return false;
        }
    }
    while (*p == '*') p++;
    return (*p == 0);
}
