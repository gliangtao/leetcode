
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

int divide(int dividend, int divisor);

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int i;
    gettimeofday(&tvStart, NULL);
    i = divide(atoi(argv[1]), atoi(argv[2]));
    gettimeofday(&tvEnd, NULL);
    printf("divide(%s, %s) == %d\n", argv[1], argv[2], i);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    DBG("Time %d.%06d, divide\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif

#define CMP(left, right) (dir1 ? (-(left + right)) : (left - right))
//4ms version
int divide(int dividend, int divisor) {
    int i;
    int ret = 0;
    if (!divisor) {
        return INT_MAX;
    }
    int dir1 = (dividend < 0);
    int dir2 = (divisor < 0);
    if (dir2) {
        if (divisor == INT_MIN) {
            return (dividend == INT_MIN);
        }
        divisor = -divisor;
    }
    if ((dividend == INT_MIN) && (divisor == 1)) {
        return dir2 ? INT_MAX : INT_MIN;
    }

    int absRv = divisor;
    int cmp;
    for (i = 0; i < (sizeof(int) * 8) - 1; i++) {
        cmp = CMP(dividend, absRv);
        if ((absRv <= 0) || (cmp <= 0)) {
            break;
        }
        absRv <<= 1;
    }
    if (cmp != 0) {
        i--;
        if (i < 0) {
            return 0;
        }
        absRv = divisor << i;
    }
    while (i >= 0) {
        if (CMP(dividend, absRv) >= 0) {
            ret += (1 << i);
            if (dividend < 0) {
                dividend += absRv;
            } else {
                dividend -= absRv;
            }
            if (dividend == 0) {
                break;
            }
        }
        i--;
        absRv >>= 1;
    }
    return (dir1 != dir2) ? -ret : ret;
}
