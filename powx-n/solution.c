

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

double myPow(double x, int n);
//int N[] = {1,1,2};
int N[] =
//{2,2,1,1};
{0,1,0,0,9};

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    double ret;
    double param;
    gettimeofday(&tvStart, NULL);
    param = strtod(argv[1], NULL);
    ret = myPow(param, atoi(argv[2]));
    gettimeofday(&tvEnd, NULL);
    
    printf("myPow(%lf): %lf\n", param, ret);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    DBG("Time %d.%06d, myPow\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif

//0ms version
double myPow(double x, int n) {
    if (n == 0) return 1;
    if (n == -1) return (1.0 / x);
    if (n == 1) return x;
    double pow = myPow(x, (n / 2));
    pow *= pow;
    return (n & 1) ? ((n < 0) ? (pow / x) : (pow * x)) : pow;
}
