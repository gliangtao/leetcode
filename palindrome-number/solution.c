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
bool isPalindrome(int x);
int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    char* result;
    gettimeofday(&tvStart, NULL);
    result = isPalindrome(atoi(argv[1])) ? "true" : "false";
    gettimeofday(&tvEnd, NULL);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, isPalindrome(%s): %s\n", ds, dus, argv[1], result);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#endif

#if 0
// 80ms version
bool isPalindrome(int x) {
    int d = 1000000000;
    int m;
    int n = x;
    if (x < 0) {
        return false;
    }
    if (x >= 10) {
        while (0 == (n = (x / d))) {
            d /= 10;
        }
        m = x % 10;
        while (true) {
            //printf("x %d, d %d, m %d, n %d\n", x, d, m, n);
            if (m != n) {
                return false;
            }
            x -= n * d;
            x /= 10;
            d /= 100;
            if (d <= 1) {
                return true;
            }
            n = x / d;
            m = x % 10;
        }
    }
    return true;
}
#endif

// This is one 68-72ms version
bool isPalindrome(int x) {
    int d = 1;
    int m;
    int n = x;
    if (x < 0) {
        return false;
    }
    if (x >= 10) {
        while ((n = (x / d)) > 9) {
            d += (d << 3) + d;
        }
        m = x % 10;
        while (true) {
            if (m != n) {
                return false;
            }
            x -= n * d;
            x /= 10;
            d /= 100;
            if (d <= 1) {
                return true;
            }
            n = x / d;
            m = x % 10;
        }
    }
    return true;
}
