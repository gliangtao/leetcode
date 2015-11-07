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


static char* W[] =
//{ "a", "b", "c", "d", "e" };
//{ "What","must","be","shall","be." };
{"Imagination","is","more","important","than","knowledge."};

char** fullJustify(char** words, int wordsSize, int maxWidth, int* returnSize);

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    char** ret;
    int retSize;
    gettimeofday(&tvStart, NULL);
    ret = fullJustify(W, sizeof(W) / sizeof(W[0]), 11, &retSize);
    gettimeofday(&tvEnd, NULL);

    printf("fullJustify(): %d\n", retSize);
    for (int i = 0; i < retSize; i++) printf("\t\"%s\"\n", ret[i]);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, fullJustify\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif

#include <stdlib.h>
#include <string.h>

/*
Given an array of words and a length L, format the text such that each line has exactly L
characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each
line. Pad extra spaces ' ' when necessary so that each line has exactly L characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on
a line do not divide evenly between words, the empty slots on the left will be assigned more spaces
than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.

Return the formatted lines as:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
Note: Each word is guaranteed not to exceed L in length
*/

static char* buildLine(int nChars, int nWords, int N, char** words, int start) {
    char* line = (char*)malloc(N + 1);
    if (line) {
        line[N] = '\0';
        if (!nWords) {
            memcpy(line, words[start], nChars);
            memset(line + nChars, ' ', N - nChars);
            return line;
        }
        int nSpaces = N - nChars;
        int nAvgSpaces = nSpaces / nWords;
        int lNum = nSpaces % nWords;
        int i;
        char* p = line;
        strcpy(p, words[start++]);
        while (*p) p++;
        for (i = 0; i < lNum; i++) {
            memset(p, ' ', nAvgSpaces + 1);
            p += nAvgSpaces + 1;
            strcpy(p, words[start++]);
            while (*p) p++;
        }
        for (; i < nWords; i++) {
            memset(p, ' ', nAvgSpaces);
            p += nAvgSpaces;
            strcpy(p, words[start++]);
            while (*p) p++;
        }
    }
    return line;
}

static char* buildLastLine(int nChars, int nWords, int N, char** words, int start) {
    char* line = (char*)malloc(N + 1);
    if (line) {
        line[N] = '\0';
        if (!nWords) {
            memcpy(line, words[start], nChars);
            memset(line + nChars, ' ', N - nChars);
            return line;
        }
        int nSpaces = N - nChars;
        int nAvgSpaces = nSpaces / nWords;
        int lNum = nSpaces % nWords;
        int i;
        char* p = line;
        strcpy(p, words[start++]);
        while (*p) p++;
        for (i = 0; i < nWords; i++) {
            *p++ = ' ';
            strcpy(p, words[start++]);
            while (*p) p++;
        }
        memset(p, ' ', N - nChars - nWords);
    }
    return line;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
//0ms version
char** fullJustify(char** words, int wordsSize, int maxWidth, int* returnSize) {
    const int N = maxWidth;
    int retSize = 0;
    char** ret = (char**)malloc(sizeof(char*) * (wordsSize + 1));
    if (!ret) goto bail;
    char** pp = ret;
    char* line;
    int i;
    int nWords = 0, nChars = 0;
    int curLen, start;
    if (!words || !wordsSize || !maxWidth) {
        *ret = strdup("");
        retSize = 1;
        goto bail;
    }

    for (start = i = 0; i < wordsSize; i++) {
        curLen = strlen(words[i]);
        if (nChars + nWords + curLen > N) {
            //Arrange for one new line
            line = buildLine(nChars, nWords - 1, N, words, start);
            if (!line) goto bail;
            *pp++ = line;
            nChars = 0;
            nWords = 0;
            start = i;
        }
        nWords++;
        nChars += curLen;
    }
    line = buildLastLine(nChars, nWords - 1, N, words, start);
    if (!line) goto bail;
    *pp++ = line;
    retSize = (pp - ret);
    pp = (char**)realloc(ret, sizeof(char*) * retSize);
    if (pp) ret = pp;

bail:
    if (returnSize) *returnSize = retSize;
    return ret;
}
