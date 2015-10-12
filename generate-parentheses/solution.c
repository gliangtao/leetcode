#include <stdlib.h>

#ifdef MY_UNIT_TEST
#define DBG(str...) printf(str)
#else
#define DBG(str...)
#endif

#ifdef MY_UNIT_TEST

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>

char** generateParenthesis(int n, int* returnSize);

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int retSize;
    gettimeofday(&tvStart, NULL);
    generateParenthesis(atoi(argv[1]), &retSize);
    gettimeofday(&tvEnd, NULL);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, threeSum\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#endif

#include <stdlib.h>

typedef struct MyNode {
    char* str;
    struct MyNode* next;
} MyNode;

static char** convertNodes(MyNode* head, int size) {
    if (!head || (size <= 0)) {
        return NULL;
    }
    char** ret = (char**)malloc(sizeof(char*) * size);
    if (!ret) {
        return NULL;
    }
    char** pp = ret + size;
    while (head != NULL) {
        *(--pp) = head->str;
        head = head->next;
    }
    return ret;
}

static void releaseNodes(MyNode* head) {
    MyNode* p = head;
    while (p != NULL) {
        p = p->next;
        free(head);
        head = p;
    }
}

static int count = 0;
static MyNode* getNewStr(char* buf, int bufLen, int lastLeftPIdx) {
    MyNode* ret = (buf && bufLen) ? (MyNode*)malloc(sizeof(MyNode)) : NULL;
    if (ret) {
        char* str = (char*)malloc(bufLen + 1);
        if (str) {
            int leftLen = lastLeftPIdx + 1;
            memcpy(str, buf, leftLen);
            memset(str + leftLen, ')', bufLen - leftLen);
            str[bufLen] = '\0';
            DBG("lastLeftPIdx %d, str %d: %s\n", lastLeftPIdx, count++, str);
            ret->str = str;
            ret->next = NULL;
        } else {
            free(ret);
            ret = NULL;
        }
    }
    return ret;
}

//0ms version
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** generateParenthesis(int n, int* returnSize) {
    char** ret;
    MyNode* head = NULL;
    MyNode* q;
    int nRet = 0;
    const int DN = n << 1;

    char s[DN + 1];
    memset(s, '(', n);
    memset(s + n, ')', n);
    s[DN] = '\0';
    head = getNewStr(s, DN, n);
    if (!head) {
        goto bail;
    }
    nRet = 1;

    int nLP = n;
    int top;
    for (top = n - 1; top > 0;) {
        // top is index/position of the last '(', and it will be changed to ')'
        // To make a valid change, last '(' must be at least followed by one ')', and number of '('
        // must be no less than half of 'top'
        while ((top < DN - 2) && (nLP >= ((top + 1) >> 1))) {
            s[top] = ')';
            nLP--;
            while (nLP < n) {
                s[++top] = '(';
                nLP++;
            }
            q = getNewStr(s, DN, top);
            if (q != NULL) {
                q->next = head;
                head = q;
                nRet++;
            } else {
                goto bail;
            }
        }
        // If number of preceding '(' is less than that of preceding ')', try preceding '('
        // if it exists.
        while ((top > 0) && (nLP < ((top + 4) >> 1))) {
            while (s[--top] == ')');
            nLP--;
        }
    }

bail:
    if (returnSize) {
        *returnSize = nRet;
    }
    ret = convertNodes(head, nRet);
    releaseNodes(head);
    return ret;
}
