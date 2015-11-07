
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

char* simplifyPath(char* path);

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    char* ret;
    int retSize;
    gettimeofday(&tvStart, NULL);
    ret = simplifyPath(argv[1]);
    gettimeofday(&tvEnd, NULL);

    printf("simplifyPath('%s'):\n             '%s'\n", argv[1], ret);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, simplifyPath\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif

/*
Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"
click to show corner cases.

Corner Cases:
Did you consider the case where path = "/../"?
In this case, you should return "/".
Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
In this case, you should ignore redundant slashes and return "/home/foo".
*/
//0ms version, O(n)
char* simplifyPath(char* path) {
    if (!path) return strdup("/");
    int len = strlen(path);
    char* ret = (char*)malloc(len + 2);
    if (ret) {
        int ch;
        int skips = 0;
        char* p = ret + len + 1;
        char* q = path + len - 1;
        *p-- = '\0';
        while ((q >= path) && ((ch = *q--) == '/'));
        while (q >= path) {
            char* lastDir = q + 1;
            if (ch == '.') {
                int t = 0;
                while ((ch = *q--) == '.') t++;
                if ((ch == '/') && (t <= 1)) {
                    skips += t;
                    while ((q >= path) && ((ch = *q--) == '/'));
                    continue;
                }
            }
            if (--skips < 0) {
                skips = 0;
                while (*lastDir != '/') *p-- = *lastDir--;
                q = lastDir;
                *p-- = '/';
            } else {
                while (*q != '/') q--;
            }
            while ((q >= path) && ((ch = *q--) == '/'));
        }
        if (p[1] != '/') {
            *p = '/';
        } else {
            p++;
        }

        if (p > ret) {
            memmove(ret, p, (ret - p) + len + 2);
            path = realloc(ret, (ret - p) + len + 2);
            if (path) ret = path;
        }
    }
    return ret;
}
