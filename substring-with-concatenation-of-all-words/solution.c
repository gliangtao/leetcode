#include <stdlib.h>
#include <limits.h>
#include <string.h>

#ifndef DBG
#define DBG(str...)
#endif

/**
 * You are given a string, s, and a list of words, words, that are all of the same length.
 *
 * Find all starting indices of substring(s) in s that is a concatenation of each word in words
 * exactly once and without any intervening characters.
 *
 * For example, given:
 * s: "barfoothefoobarman"
 * words: ["foo", "bar"]
 *
 * You should return the indices: [0,9]. (order does not matter).
 */

typedef struct {
    int* pi;
    int off;
    int isDup;
} MyWordItem;

static void getPi(char*p, int n, int* pi) {
    int ch;
    char* q = p;
    int k = pi[0] = 0;
    for (int i = 1; (ch = *(++q)) != 0; i++) {
        while ((k > 0) && (ch != p[k])) k = pi[k - 1];
        if (ch == p[k]) k++;
        pi[i] = k;
    }
}

static int myKmpStrStr(char* s, int slen, char* p, int* pi, int plen) {
    int i, k, j, ch;

    i = k = 0;

    while ((ch = s[i])) {
        while ((k > 0) && (ch != p[k])) k = pi[k - 1];
        if (ch == p[k]) {
            if ((k == 0) && (j = (i % plen))) {
                i += plen - j;
                continue;
            }
            if (++k == plen) {
                return (i - plen + 1);
            }
        }
        i++;
    }
    return INT_MIN;
}

static int mycmp(const void* p1, const void* p2) {
    char** ps1 = (char**)p1;
    char** ps2 = (char**)p2;
    return strcmp(*ps1, *ps2);
}

//This is one 20ms version. Could be faster if using Min-Heap for WSIZ words
// + better initialization
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
    int* ret = NULL;
    int  iRet = 0;
    size_t retSize;

    int* aPi = NULL;
    int* ppi;
    MyWordItem* aItem = NULL;
    MyWordItem* item0 = NULL;
    int i;
    if (!s || !words || !wordsSize) {
        goto bail;
    }
    const int WSIZ = wordsSize;
    const int SLEN = strlen(s);
    const int WLEN = strlen(words[0]);
    const int WRANGEL = (WSIZ - 1) * WLEN;

    if (WLEN == 0) {
        goto bail;
    }

    aItem = (MyWordItem*)malloc(sizeof(MyWordItem) * WSIZ);
    if (!aItem) {
        goto bail;
    }

    aPi = (int*)malloc(sizeof(int) * WSIZ * WLEN);
    if (!aPi) {
        goto bail;
    }

    retSize = sizeof(int) * SLEN / (WLEN);
    ret = (int*)malloc(retSize);
    if (!ret) {
        goto bail;
    }

    qsort(words, WSIZ, sizeof(char*), mycmp);

    for (ppi = aPi + WLEN, i = 1; i < WSIZ; i++) {
        aItem[i].off = -1;
        aItem[i].pi = ppi;
        aItem[i].isDup = !strcmp(words[i - 1], words[i]);
        ppi += WLEN;
    }
    item0 = aItem;
    item0->off = -1;
    item0->pi = aPi;
    item0->isDup = 0;
    DBG("str: %s\n", s);
    DBG("%d words:", WSIZ);
    i = 0;
    for (MyWordItem* item = aItem; i < WSIZ; i++) {
        DBG(",%s", words[i]);
        getPi(words[i], WLEN, item->pi);
        item++;
    }
    DBG("\n");

    int minOff, maxOff, nextOff, j;

    for (i = 0; i < WLEN;) {
        for (j = 0; j < WSIZ; j++) {
            aItem[j].off = -1;
        }
        maxOff = -1;
        for (nextOff = i; nextOff < SLEN - i;) {
            int off;
            minOff = INT_MAX;
            for (j = 0; j < WSIZ; j++) {
                DBG("minOff %d, maxOff %d, nextOff %d, j %d, off %d, isDup %d, i %d\n",
                    minOff, maxOff, nextOff, j, aItem[j].off, aItem[j].isDup, i);

                //Find left limit & starting point
                off = (aItem[j].isDup && j > 0) ? (aItem[j - 1].off + WLEN) : nextOff;
                DBG("i %d, off = %d: %s\n", i, off, s + off);
                if (aItem[j].off < off) {
                    aItem[j].off = myKmpStrStr(s + off, SLEN - off, words[j], aItem[j].pi, WLEN)
                            + off;
                    if (aItem[j].off < 0) {
                        //DBG("Not found '%s' at s[%d, len %d]\n", words[j], off, SLEN - off);
                        goto continue_outer_loop;
                    }
                }
                off = aItem[j].off;
                if (off < minOff) {
                    minOff = off;
                }
                if (off > maxOff) {
                    maxOff = off;
                }
                if (maxOff - minOff > WRANGEL) {
                    break;
                }
            }
            if (maxOff - minOff != WRANGEL) {
                nextOff += WLEN;
                off = (maxOff == SLEN - i) ? maxOff : (maxOff - WRANGEL);
                nextOff = (nextOff < off) ? off : nextOff;
                goto continue_inner_loop;
            }
            iRet++;
            //Got iRet'th result at "minOff"
            //Advance nextOff to bypass the newly found result
            nextOff = minOff + WLEN;

            if (retSize < iRet) {
                while (retSize < iRet) retSize <<= 1;
                int* p = (int*)realloc(ret, retSize);
                if (!p) {
                    iRet--;
                    goto bail;
                }
                ret = p;
            }
            ret[iRet - 1] = minOff;

continue_inner_loop:
            minOff = INT_MAX;
        }
continue_outer_loop:
        i++;
    }

bail:
    if (iRet) {
        int* buf = (int*)realloc(ret, iRet * sizeof(int));
        if (NULL != buf) {
            ret = buf;
        }
    }
#ifdef MY_UNIT_TEST
    DBG("Total %d results: ", iRet);
    for (i = 0; i < iRet; i++) {
        DBG(", %d", ret[i]);
    }
    DBG("\n");
#endif
    free(aPi);
    free(aItem);
    if (returnSize) {
        *returnSize = iRet;
    }

    return ret;
}
