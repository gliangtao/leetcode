#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/time.h>

#ifdef MY_UNIT_TEST
char* longestPalindrome(char* s);
int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    char* result;
    gettimeofday(&tvStart, NULL);
    result = longestPalindrome(argv[1]);
    gettimeofday(&tvEnd, NULL);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, Longest palindrome substring: %s\n", ds, dus, result);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#endif

#if 0
//This version will timeout
typedef struct {
    int s;
    int l;
} Node;

char* longestPalindrome(char* s) {
    if (!s || !*s) {
        return s;
    }
    int size = strlen(s);
    int l;
    int i;
    Node* c = (Node*)malloc(sizeof(Node) * size * (size));
    if (!c) {
        return NULL;
    }
    Node* p;
    Node* p2;
    p = c;
    for (i = 0; i < size; i++) {
        p->s = i;
        p->l = 0;
        p += size;
    }
    p = c + 1;
    for (i = 0; i < size - 1; i++) {
        p->s = i;
        p->l = !!(s[i] == s[i + 1]);
        p += size;
    }

    for (l = 2; l < size; l++) {
        p = c + l; //c[i][l]
        p2 = p + size - 2; //c[i+1][l-2]
        for (i = 0; i < size - l; i++) {
            int s2;
            int l2;
            s2 = p2->s;
            l2 = p2->l;

            if ((l2 == l - 2) && (s[i] == s[i + l])) {
                s2 -= 1;
                l2 += 2;
            }
            p->s = s2;
            p->l = l2;

            p += size;
            p2 += size;
        }
    }
    p = c + size - 1;
    i = p->s;
    l = p->l + 1;
    free(c);
    char* ret = (char*)malloc(l + 2);
    if (ret) {
        memcpy(ret, s + i, l + 1);
        ret[l + 1] = '\0';
    }
    return ret;
}
#endif

#if 0
// This is 16ms version
char* longestPalindrome(char* s) {
    if (!s || !*s) {
        return s;
    }
    int l, i;
    char* p = s;
    char* q;
    char* r;
    int len = strlen(s);
    char* end = s + len;
    l = 0;
    char* t = s;
    int ltmp;
    for (p = s; p < end; p++) {
        q = p;
        r = p + 1;
        while ((q >= s) && (r <= end) && (*q == *r)) {
            q--;
            r++;
        }
        ltmp = r - q - 2;
        if (l < ltmp) {
            l = ltmp;
            t = q + 1;
        }
    }
    for (p = s; p < end - 1; p++) {
        q = p;
        r = p + 2;
        while ((q >= s) && (r <= end) && (*q == *r)) {
            q--;
            r++;
        }
        ltmp = r - q - 2;
        if (l < ltmp) {
            l = ltmp;
            t = q + 1;
        }
    }
    l++;
    char* ret = (char*)malloc(l + 1);
    if (ret) {
        memcpy(ret, t, l);
        ret[l] = '\0';
    }
    return ret;
}
#endif

#if 0
// This is 224ms version
char* longestPalindrome(char* s) {
    if (!s || !*s) {
        return s;
    }
    int l = 0;
    int ltmp;
    char* p = s;
    char* end = s + strlen(s);
    char* q;
    char* r;
    char* t;
    char* pos = s;
    int ch;
    while (p < end - l) {
        ltmp = 0;
        ch = *p;
        t = p + l;
        while ((t < end) && ((t = strchr(t + 1, ch)) != NULL)) {
            r = t - 1;
            q = p + 1;
            while ((q <= r) && (*q == *r)) {
                q++;
                r--;
            }
            if (q > r) {
                l = ltmp = t - p;
                pos = p;
            }
        }
        p++;
    }
    l++;
    char* ret = (char*)malloc(l + 1);
    if (ret) {
        memcpy(ret, pos, l);
        ret[l] = '\0';
    }
    return ret;
}
#endif

#if 0
//This is 0ms version from LianWei
char* longestPalindrome(char* s) {
int i = 0, n = strlen(s);
int longest = 0, longestx;
char *str;

if (n == 1)
    return s;

do {
    int k = 1;
    int j = 1;

    if (((n - i) * 2 + 1) < longest)
        break;

    while (i + k < n && s[i] == s[i+k])
        k++;

    while(i - j >= 0 && i + k - 1 + j < n && s[i - j] == s[i + k - 1 + j])
        j++;

    if ((j - 1) * 2 + k > longest) {
        longest = (j - 1) * 2 + k;
        longestx = i - (j - 1);
    }

    i += k -1 > 0 ? k - 1 : 1;
} while (i < n - 1);

str = (char *) malloc(longest + 1);
memcpy(str, s + longestx, longest);
str[longest] = 0;

return str;
}

#endif

//This is also a 0ms version. Refer to LianWei's code
char* longestPalindrome(char* s) {
    if (!s || !*s) {
        return s;
    }
    char* p, *q, *r, *t, *end;
    int slen = strlen(s);
    int ch;
    int ltmp;
    end = s + slen;
    t = s;
    int l = 1;
    for (p = s; p <= end - ((l + 1) >> 1);) {
        ch = *p;
        r = p + 1;
        while ((r != end) && (*r == ch)) r++;
        ltmp = r - p;
        q = p - 1;
        p += ltmp;
        while ((q >= s) && (r <= end) && (*q == *r)) {
            r++;
            q--;
        }
        ltmp += (r - p) * 2;
        if (l < ltmp) {
            l = ltmp;
            t = q + 1;
        }
    }
    char* ret = (char*)malloc(l + 1);
    if (ret) {
        memcpy(ret, t, l);
        ret[l] = '\0';
    }
    return ret;
}

