
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

int strStr(char* haystack, char* needle);

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int i;
    gettimeofday(&tvStart, NULL);
    i = strStr(argv[1], argv[2]);
    gettimeofday(&tvEnd, NULL);
    if (i >= 0) {
        printf("Found '%s' in '%s', pos %d (%s)\n", argv[2], argv[1], i, argv[1] + i);
    } else {
        printf("Fail to find '%s' in '%s'\n", argv[2], argv[1]);
    }
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    DBG("Time %d.%06d, myqsort\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif

#if 0
//This version times out
int strStr(char* haystack, char* needle) {
    if (!haystack || !needle) {
        return 0;
    }
    char* p;
    char* q;
    char* next;
    int ch;
    for (next = haystack; *next != 0; next++) {
        q = needle;
        p = next;
        while (1) {
            if (!(ch = *q++)) {
                return (next - haystack);
            }
            if (ch != *p++) {
                break;
            }
        }
    }
    return -1;
}
#endif


#if 0
//0ms version, using KMP algorithm
static void getPi(char* p, int n, int* pi) {
    int ch;
    int k = pi[0] = -1;
    for (int i = 1; i < n; i++) {
        ch = p[i];
        while ((k >= 0) && (ch != p[k + 1])) k = pi[k];
        if (ch == p[k + 1]) {
            k++;
        }
        pi[i] = k;
    }
}

int strStr(char* haystack, char* needle) {
    if (!haystack || !needle || !*needle) {
        return 0;
    }
    const int N = strlen(needle);
    int pi[N];

    getPi(needle, N, pi);
    int k;
    int ch;

    for (int i = 0, k = -1; (ch = haystack[i]) != 0; i++) {
        while ((k >= 0) && (ch != needle[k + 1])) k = pi[k];
        if (ch == needle[k + 1]) {
            k++;
            if (k == N - 1) {
                return (i - N + 1);
            }
        }
    }
    return -1;
}
#endif


#if 0
//Another 0ms version, also using KMP algorithm
static void getPi(char* p, int n, int* pi) {
    int ch;
    int k = pi[0] = 0;
    for (int i = 1; (ch = p[i]) != 0; i++) {
        while ((k > 0) && (ch != p[k])) k = pi[k - 1];
        if (ch == p[k]) {
            k++;
        }
        pi[i] = k;
    }
}
#endif

//More complex getPi(), still 0ms
static void getPi(char*p, int n, int* pi) {
    int ch;
    char* q = p;
    int k = pi[0] = 0;
    for (int i = 1; (ch = *(++q)) != 0; i++) {
        while ((k > 0) && (ch != p[k])) k = pi[k - 1];
        if (ch == p[k]) k++;
        pi[i] = k;
    }
}

int strStr(char* haystack, char* needle) {
    if (!haystack || !needle || !*needle) {
        return 0;
    }
    int k;
    int ch;
    char* s;

    const int N = strlen(needle);
    int pi[N];
    getPi(needle, N, pi);
    for (k = 0, s = haystack; (ch = *s++) != 0;) {
        while ((k > 0) && (ch != needle[k])) k = pi[k - 1];
        if (ch == needle[k]) {
            k++;
            if (k == N) {
                return ((s - haystack) - N);
            }
        }
    }
    return -1;
}
