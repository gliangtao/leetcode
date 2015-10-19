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

char* multiply(char* num1, char* num2);

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    char* s;
    gettimeofday(&tvStart, NULL);
    s = multiply(argv[1], argv[2]);
    gettimeofday(&tvEnd, NULL);
    
    printf("%s X %s = \n%s\n", argv[1], argv[2], s);
    free(s);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    DBG("Time %d.%06d, multiply\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif
/*
Given two numbers represented as strings, return multiplication of the numbers as a string.

Note: The numbers can be arbitrarily large and are non-negative.
*/
#include <stdlib.h>

#define A2D(ch) (ch - '0')
#define D2A(d)  (d + '0')

//4ms version, Time O(m*n), space O(m+n) (for return value)
char* multiply(char* num1, char* num2) {
    while (num1) {
        if (*num1 == '0') {
            num1++;
        } else {
            break;
        }
    }
    while (num2) {
        if (*num2 == '0') {
            num2++;
        } else {
            break;
        }
    }
    const int N1 = strlen(num1);
    const int N2 = strlen(num2);
    char* ret = (char*)malloc(N1 + N2 + 2);
    if (!ret) return NULL;
    memset(ret, 0, N1 + N2 + 2);
    if (!N1 || !N2) {
        *ret = '0';
        return ret;
    }

    char *p, *q;
    int d1, d2, d3, i, j;
    for (i = N1 - 1; i >= 0; i--) {
        d1 = A2D(num1[i]);
        for (j = N2 - 1; j >= 0; j--) {
            p = ret + 2 + i + j;
            d2 = A2D(num2[j]);
            //printf("ret[%d] %d + %d * %d = %d\n", i + j, *p, d1, d2, *p + d1 * d2);
            *p += d1 * d2;
            while (*p >= 10) {
                p[-1] += (*p / 10);
                *p %= 10;
            }
        }
    }

    for (i = 0; i <= N1 + N2; i++) ret[i] += '0';

    for (p = ret; *p == '0'; p++);
    if (p != ret) {
        q = strdup(p);
        if (q) {
            free(ret);
            ret = q;
        }
    }

    return ret;
}
