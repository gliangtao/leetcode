

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

int mySqrt(int x);

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int ret;
    gettimeofday(&tvStart, NULL);
    ret = mySqrt(atoi(argv[1]));
    gettimeofday(&tvEnd, NULL);
    
    printf("mySqrt(%s): %d\n", argv[1], ret);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    DBG("Time %d.%06d, mySqrt\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif

#if 0
//4ms version
int mySqrt(int x) {
    int l, r, m;
    int64_t d, d2;
    if (x < 0) return 0;
    if (x <= 1) return x;
    for (l= 1, r = x - 1; l <= r;) {
        d = m = (l + r) >> 1;
        d *= m;
        d -= x;
        if (d < 0) {
            l = m + 1;
        } else if (d > 0) {
            r = m - 1;
        } else return m;
    }
    return r;
}
#endif

//8ms version, no int64_t, no function call, Newton method
int mySqrt(int x) {
    if (x < 2) return x;
    int l, r, m, d;
    for (l = 1, r = x - 1; l <= r;) {
        m = (l + r) >> 1;
        d = m - (x / m);
        #ifdef MY_UNIT_TEST
        printf("l %d, r %d, m %d, x/m %d, d %d\n", l, r, m, x/m, d);
        #endif
        if (d < 0) {
            l = m + 1;
        } else if (d > 0) {
            r = m - 1;
        } else return m;
    }
    return r;
}
