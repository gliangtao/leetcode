#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>

#ifdef MY_UNIT_TEST
int reverse(int x);
int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int result;
    gettimeofday(&tvStart, NULL);
    result = reverse(atoi(argv[1]));
    gettimeofday(&tvEnd, NULL);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, reversed integer: %d\n", ds, dus, result);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#endif


#if 0
//https://leetcode.com/discuss/60613/simple-4ms-c-solution
#define INT_MAX 2147483647
#define INT_MIN -2147483648
int reverse(int x) {
    long long out=0;
    int sign = x >= 0 ? 1:-1;
    x=abs(x);
    while(x>0){
        out = out * 10 + x % 10;
        if(out > INT_MAX || out*sign < INT_MIN)
            return 0;
        x /= 10;
    }
    return out*sign;
}
#endif

// 4ms - 8ms
int reverse(int x) {
    int xneg = (x < 0);
    int xabs = xneg ? -x : x;
    int rabs = 0;
    int nv;
    int int_max = (int)((unsigned int)(-1) >> 1);
    int int_min = int_max + 1;
    int maxv = int_max / 10 - 1;
    int m;
    if (x == int_min) {
        return 0;
    }
#ifdef MY_UNIT_TEST
    printf("maxv = 0x%08x (INT_MIN = 0x%08x, %d)\n", maxv, int_max + 1, int_max + 1);
#endif
    while (xabs) {
        m = xabs % 10;
        xabs /= 10;
#ifdef MY_UNIT_TEST
        printf("xabs = 0x%08x, rabs = 0x%08x, maxv = 0x%08x\n", xabs, rabs, ((int_max - m) / 10));
#endif
        if (rabs > ((int_max - m) / 10)) {
            return 0;
        }
        nv = (rabs << 3) + (rabs << 1) + m;
        rabs = nv;
    }
    return xneg ? -rabs : rabs;
}
