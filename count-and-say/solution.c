#include <string.h>

//0ms version
/*
 * The count-and-say sequence is the sequence of integers beginning as follows:
 * 1, 11, 21, 1211, 111221, ...
 * 1 is read off as "one 1" or 11.
 * 11 is read off as "two 1s" or 21.
 * 21 is read off as "one 2, then one 1" or 1211.
 * Given an integer n, generate the nth sequence.
 *
 * Note: The sequence of integers will be represented as a string.
 */
char* countAndSay(int n) {
    switch (n) {
    case 1:
        return strdup("1");
    case 2:
        return strdup("11");
    case 3:
        return strdup("21");
    case 4:
        return strdup("1211");
    case 5:
        return strdup("111221");
    default:
        if (n <= 0) {
            return NULL;
        }
        break;
    }
    char* t = countAndSay(n - 1);
    char* ret;

    int tlen = strlen(t);
    ret = (char*)malloc((tlen << 1) + 1);

    char* p;
    char* q;
    char* mark;
    int ch;
    int i;

    for (p = t, q = ret; (ch = *p) != 0;) {
        mark = p;
        while (ch == *(++p));
        i = sprintf(q, "%d%c", (p - mark), ch);
        if (i < 0) {
            break; 
        }
        q += i;
    }
    *q = '\0';
    free(t);
    return ret;
}
