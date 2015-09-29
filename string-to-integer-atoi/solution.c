#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>

#ifdef MY_UNIT_TEST
int myAtoi(char* str);
int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int result;
    gettimeofday(&tvStart, NULL);
    result = myAtoi(argv[1]);
    gettimeofday(&tvEnd, NULL);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, atoi(%s): %d\n", ds, dus, argv[1], result);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#endif

#if 0
//This is one invalid solution!!!
int myAtoi(char* str) {
    int got_digit = 0;
    int sign = 1;
    unsigned int vabs = 0;
    if (!str) {
        return 0;
    }
    char* p = str;
    int ch;
    unsigned int digit = 0;
    while (isspace((ch = *p))) {
        p++;
    }
    if (ch == '-') {
        sign = -1;
        p++;
    } else if (ch == '+') {
        sign = 1;
        p++;
    }
    while (isdigit(ch = *p++)) {
        digit = ch - '0';
        vabs = (vabs << 3) + (vabs << 1) + digit;
        
        if ((sign > 0) && (vabs > INT_MAX)) {
            vabs = INT_MAX;
        } else if ((sign < 0) && (vabs > ((unsigned int)(INT_MIN)))) {
            vabs = (unsigned int)INT_MIN;
        }
    }
    return (sign > 0) ? vabs : -vabs;
}
//END one invalid solution!!!
#endif

//One 4ms-8ms verion
int myAtoi(char* str) {
    int got_digit = 0;
    int sign = 1;
    unsigned int vabs = 0;
    if (!str) {
        return 0;
    }
    char* p = str;
    int ch;
    unsigned int digit = 0;
    while (isspace((ch = *p))) {
        p++;
    }
    if (ch == '-') {
        sign = -1;
        p++;
    } else if (ch == '+') {
        sign = 1;
        p++;
    }
    while (isdigit(ch = *p++)) {
        digit = ch - '0';
        if ((sign > 0) && (vabs > ((INT_MAX - digit) / 10))) {
            vabs = INT_MAX;
            break;
        } else if ((sign < 0) && (vabs > (((unsigned int)(INT_MIN) - digit) / 10))) {
            vabs = (unsigned int)INT_MIN;
            break;
        }
        vabs = (vabs << 3) + (vabs << 1) + digit;
    }
    if (sign > 0) {
        return vabs;
    }
    return (0 - vabs);
}
