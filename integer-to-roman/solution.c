
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>

#ifdef MY_UNIT_TEST

char* intToRoman(int num);
int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    char* result;
    gettimeofday(&tvStart, NULL);
    result = intToRoman(atoi(argv[1]));
    gettimeofday(&tvEnd, NULL);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, intToRoman(%d): %s\n", ds, dus, atoi(argv[1]), result);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#endif


const static int  SV[] = {1,    5,   10,  50, 100, 500, 1000};
const static char SC[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
#define SN          (sizeof(SV) / sizeof(SV[0]))
#define SN_MAX      (SN - 1)
static char buf[1024];

#if 0
//This should be the correct-er solution, but it produces different result "VL" for 45, not "XLV"
char* intToRoman(int num) {
    int i = SN - 1;
    int j;
    char* p = buf;
    int delta;
    while (num >= SV[SN_MAX]) {
        num -= SV[SN_MAX];
        *p++ = SC[SN_MAX];
    }
    for (i = SN_MAX; (i >= 0) && (num > 0);) {
        while (i && (num < SV[i])) {
            i--;
        }
        delta = SV[i + 1] - num;
        for (j = i; j >= 0; j--) {
            if (SV[j] < delta) {
                if ((i != j) && ((SV[i + 1] - SV[j + 1]) <= num) && (SV[i + 1] != 2 * SV[j + 1])) {
                    num -= (SV[i + 1] - SV[j + 1]);
                    *p++ = SC[j + 1];
                    *p++ = SC[i + 1];
                }
                break;
            }
            if (SV[j] == delta) {
                if (SV[i + 1] != 2 * SV[j]) {
                    num -= (SV[i + 1] - SV[j]);
                    *p++ = SC[j];
                    *p++ = SC[i + 1];
                }
                break;
            }
        }
        while (num >= SV[i]) {
            num -= SV[i];
            *p++ = SC[i];
        }
    }
    *p++ = '\0';
    return buf;
}
#endif

#if 1
//20ms accepted version
char* intToRoman(int num) {
    static char buf[1024];
    int s[7]={0};
    int Roman[7]={1000,500,100,50,10,5,1};
    char CH[7]={'M','D','C','L','X','V','I'};
    int i=0;
    char* p = buf;
    while (i <= 6) {
        s[i] = num/Roman[i];
        num %= Roman[i];
        i++;
    }
    for (i=0; i <= 6; i++) {
        if (s[i] == 1 && i < 6 && s[i+1] == 4) {
            continue;
        }
        if (s[i] == 4) {
            if (s[i-1] == 1) {
                *p++ = CH[i];
                *p++ = CH[i - 2];
            } else {
                *p++ = CH[i];
                *p++ = CH[i - 1];
            }
        } else {
            for (int j = s[i]; j > 0; j--) *p++ = CH[i];
        }
    }
    *p++ = '\0';
    return buf;
}
#endif
