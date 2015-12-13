#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>

#ifdef MY_UNIT_TEST
#define false 0
#define true 1
typedef int bool;
bool isMatch(char* s, char* p);
int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    char* result;
    gettimeofday(&tvStart, NULL);
    result = isMatch(argv[1], argv[2]) ? "true" : "false";
    gettimeofday(&tvEnd, NULL);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, isMatch(\"%s\", \"%s\"): %s\n", ds, dus, argv[1], argv[2], result);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#endif

#if 0
bool isMatch(char* s, char* p) {
    if (!s || !p) {
        return !p;
    }
    if (!*s) {
        return !*p;
    }
    char* ps;
    char* pp;
    int chs;
    int chp;
    for (ps = s, pp = p; (chp = *pp);) {
        if (chp == '.') {
            if (pp[1] == '*') {
                pp += 2;
                chp = *pp;
                while ((chs = *ps) && (chs != chp)) {
                    ps++;
                }
                continue;
            } else if (*ps) {
                pp++;
                ps++;
            } else {
                break;
            }
        } else if (chp) {
            if (pp[1] == '*') {
                while (*ps == chp) {
                    ps++;
                }
                pp += 2;
                continue;
            } else if (chp == *ps) {
                pp++;
                ps++;
                continue;
            }
            break;
        } else {
            break;
        }
    }
    return (*pp == *ps);
}
#endif

#if 0
//0ms version from other leetcoder
bool isMatch(char* s, char* p) {
    const int SLEN = strlen(s);
    bool matchs[SLEN+1];
    memset(matchs, 0, sizeof(matchs));
    matchs[0] = true;
    while(p[0] != '\0'){
        if('*' == p[1]){
            for(int i = 1; i <= SLEN; ++i)
                if(!matchs[i] && matchs[i-1] && ('.' == p[0] || p[0] == s[i-1]))
                    matchs[i] = true;
            p = p + 2;
        }else{
            for(int i = SLEN; i >=0; --i)
                if(i!=0 && matchs[i-1] && ('.' == p[0] || p[0] == s[i-1]))  matchs[i] = true;
                else matchs[i] = false;
            ++p;
        }
    }
    return matchs[SLEN];
}
#endif

#if 0
//0ms version
bool isMatch(char* s, char* p) {
    const int SLEN = strlen(s);
    const int PLEN = strlen(p);
    int c[SLEN + 1];
    int si;
    int ch;
    memset(c + 1, 0, sizeof(c[0]) * SLEN);
    c[0] = 1;

    while ((ch = *p)) {
        if (p[1] == '*') {
            for (si = 1; si <= SLEN; si++) {
                if (c[si - 1] && !c[si] && ((ch == '.') || (ch == s[si - 1]))) {
                    c[si] = true;
                }
            }
            p += 2;
        } else {
            for (si = SLEN; si > 0; si--) {
                c[si] = c[si - 1] && ((ch == '.') || (ch == s[si - 1]));
            }
            c[0] = 0;
            p++;
        }
    }
    return c[SLEN];
}
#endif

//0ms version
bool isMatch(char* s, char* p) {
    const int SLEN = strlen(s);
    int c[SLEN + 1];
    int i, chp;
    memset(c, 0, sizeof(int) * (SLEN + 1));
    c[0] = 1;
    while ((chp = *p)) {
        if (p[1] == '*') {
            for (i = 0; i < SLEN; i++) {
                if (c[i] && !c[i + 1] && ((s[i] == chp) || ('.' == chp))) c[i + 1] = 1;
            }
            p += 2;
        } else {
            for (i = SLEN - 1; i >= 0; i--) {
                c[i + 1] = (c[i] && ((s[i] == chp) || ('.' == chp)));
            }
            c[0] = 0;
            p++;
        }
    }
    return (c[SLEN] != 0);
}
