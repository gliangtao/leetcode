/**
 * Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
Note:
Although the above answer is in lexicographical order, your answer could be in any order you want.
*/
#include <stdlib.h>
#include <string.h>

static char* D2L[] = { "cba", "fed", "ihg", "lkj", "onm", "srqp", "vut", "zyxw" };
static int D2LS[] =  { 3,     3,     3,     3,     3,     4,      3,     4      };

#define D2LI(ch)    ((unsigned int)(ch - '2'))
#define ND2L        (sizeof(D2L) / sizeof(D2L[0]))

//This is 0ms version
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** letterCombinations(char* digits, int* returnSize) {
    char** ret = NULL;
    int nRet = 0;
    if (!digits || !*digits) {
        goto bail;
    }
    unsigned int idx;

    int nTotal = 1;
    int totalLen = 0;
    char* p = digits;
    int ch;

    while ((ch = *p++)) {
        idx = D2LI(ch);
        if (idx < ND2L) {
            nTotal *= D2LS[idx];
            totalLen++;
        }
    }

    ret = (char**)malloc(sizeof(char*) * nTotal);
    if (!ret) {
        goto bail;
    }
    memset(ret, 0, sizeof(char*) * nTotal);
    int i, j;
    for (i = 0; i < nTotal; i++) {
        char* p = (char*)malloc(totalLen + 1);
        if (!p) {
            for (i = i - 1; i >= 0; i--) {
                free(ret[i]);
            }
            free(ret);
            goto bail;
        }
        p[totalLen] = '\0';
        ret[i] = p;
    }

    p = digits;

    totalLen = 0;
    nTotal = 1;
    char** m;
    char** n;
    while ((ch = *p++)) {
        idx = D2LI(ch);
        if (idx < ND2L) {
            m = n = ret;
            int subSize = D2LS[idx];
            char* q = D2L[idx];
            ch = q[subSize - 1];
            for (j = nTotal; j > 0; j--) {
                *(*n++ + totalLen) = ch;
            }
            for (i = subSize - 2; i >= 0; i--) {
                ch = q[i];
                for (j = nTotal; j > 0; j--) {
                    memcpy(*n, *m++, totalLen);
                    *(*n++ + totalLen) = ch;
                }
            }
            nTotal *= D2LS[idx];
            totalLen++;
        }
    }

    nRet = nTotal;

bail:
    if (returnSize) {
        *returnSize = nRet;
    }
    return ret;
}
