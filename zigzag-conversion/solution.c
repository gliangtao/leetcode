#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/time.h>

#ifdef MY_UNIT_TEST
char* convert(char* s, int numRows);
int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    char* result;
    gettimeofday(&tvStart, NULL);
    result = convert(argv[2], atoi(argv[1]));
    gettimeofday(&tvEnd, NULL);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, converted string: %s\n", ds, dus, result);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#endif

//This is one 8ms version
char* convert(char* s, int numRows) {
    if (!s || (numRows <= 0)) {
        return NULL;
    }
    int len = strlen(s);
    char* ret = (char*)malloc(len + 1);
    if (!ret) {
        return NULL;
    }
    ret[len] = '\0';
    if (numRows == 1) {
        memcpy(ret, s, len);
        return ret;
    }
    int k = (numRows << 1) - 2;
    int i = 0;
    int j = 0;
    char* p = ret;
    for (j = 0; j < len; j += k) {
        *p++ = s[j];
    }
    for (i = 1; i < numRows - 1; i++) {
        for (j = 0; j < len; j += k) {
            if (i + j < len) {
                *p++ = s[i + j];
                if (k - i + j < len) {
                    *p++ = s[k - i + j];
                    continue;
                }
            }
            break;
        }
    }
    for (j = numRows - 1; j < len; j += k) {
        *p++ = s[j];
    }
    return ret;
}
