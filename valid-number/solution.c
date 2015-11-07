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

bool isNumber(char* s);

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    bool ret;
    gettimeofday(&tvStart, NULL);
    ret = isNumber(argv[1]);
    gettimeofday(&tvEnd, NULL);

    printf("isNumber(%s): %d\n", argv[1], ret);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, isNumber\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif
/*
Validate if a given string is numeric.

Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
Note: It is intended for the problem statement to be ambiguous. You should gather all requirements
up front before implementing one.

Update (2015-02-10):
The signature of the C++ function had been updated. If you still see your function signature accepts
a const char * argument, please click the reload button  to reset your code definition.
*/


//http://www.regular-expressions.info/floatingpoint.html
//^[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?$
//8ms version
bool isNumber(char* s) {
    char* p = s;
    char* limit;
    int state = 0;
    int ch;
    if (!p) return false;
    int hasDigit = 0;
    while ((ch = *p) && isspace(ch)) p++;
    if (!ch) return false;

    while ((ch == '+') || (ch == '-')) {
        if (state != 1) {
            state = 1;
            ch = *(++p);
        } else {
            return false;
        }
    }
    state = 1;
    while (isdigit(ch)) {
        if (state != 2) {
            hasDigit = 1;
            state = 2;
        }
        ch = *(++p);
    }
    while (ch == '.') {
        if (state != 3) {
            state = 3;
            ch = *(++p);
        } else {
            return false;
        }
    }
    while (isdigit(ch)) {
        if (state != 4) {
            hasDigit = 1;
            state = 4;
        }
        ch = *(++p);
    }
    if (!hasDigit) return false;
    while ((ch == 'E') || (ch == 'e')) {
        if (state != 5) {
            state = 5;
            ch = *(++p);
        } else {
            return false;
        }
    }
    if (state >= 5) {
        hasDigit = 0;
        while ((ch == '+') || (ch == '-')) {
            if (state != 1) {
                state = 1;
                ch = *(++p);
            } else {
                return false;
            }
        }
        state = 6;
        while (isdigit(ch)) {
            if (state != 7) {
                hasDigit = 1;
                state = 7;
            }
            ch = *(++p);
        }
        if (!hasDigit) return false;
    }
    while (isspace(ch)) ch = *(++p);
    return (ch == '\0');
}
