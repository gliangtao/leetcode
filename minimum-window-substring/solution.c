/*
Given a string S and a string T, find the minimum window in S which will contain all the characters
in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".

If there are multiple such windows, you are guaranteed that there will always be only one unique
minimum window in S.
*/

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

char* minWindow(char* s, char* t);

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    char* ret;
    gettimeofday(&tvStart, NULL);
    ret = minWindow(argv[1], argv[2]);
    gettimeofday(&tvEnd, NULL);

    printf("minWindow('%s', '%s'): '%s'\n", argv[1], argv[2], ret);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, minWindow\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif

#if 0
#define MAX_CH      26
#define CH2IDX(ch)  (ch - 'a')
#else
#define MAX_CH      256
#define CH2IDX(ch)  (ch)
#endif

#if 0
//This version combines duplicate characters in T into one character. Not accepted by Leetcode
char* minWindow(char* s, char* t) {
    char* ret = NULL;
    int cLeft = 1;
    int cTotal = 0;
    int ch, i, j, k, bestStart, bestLen;

    if (!s || !t || !(*s) || !(*t)) goto bail;
    const int SLEN = strlen(s);
    const int TLEN = strlen(t);

    char *sp, *tp;
    int cRaw[MAX_CH];
    int cHeap[MAX_CH];

    for (i = MAX_CH - 1; i >= 0; i--) {
        cRaw[i] = -1;
        cHeap[i] = 0;
    }

    for (tp = t; (ch = *(tp++)) != '\0';) {
        ch = CH2IDX(ch);
        if (cRaw[ch] < 0) {
            cRaw[ch] = 0;
            cTotal++;
        }
    }

    for (i = 0, cLeft = cTotal; (ch = s[i++]) != '\0';) {
        ch = CH2IDX(ch);
        if (cRaw[ch] >= 0) { //ch found in T
            if (cRaw[ch] == 0) { // first time found
                cLeft--;
            }
            if (cLeft < 0) {
                cHeap[0] = i;
                fixMinHeap(cHeap, cTotal, 0);
                if (i - cHeap[0] <= bestLen) {
                    bestStart = cHeap[0] - 1;
                    bestLen = i - bestStart;
                }
                continue;
            }
            cRaw[ch] = i;
            if (!cLeft) {
                // Build heap
                for (j = 0, k = 0; j < MAX_CH; j++) {
                    if (cRaw[j] > 0) {
                        cHeap[k++] = cRaw[j];
                        if (k >= cTotal) break;
                    }
                }
                for (j = ((cTotal - 1) >> 1); j >= 0; j--) fixMinHeap(cHeap, cTotal, j);
                cLeft = -1;
                bestStart = cHeap[0] - 1;
                bestLen = i - bestStart;
            }
        }
    }

bail:
    if (cLeft <= 0) {
        ret = strndup(s + bestStart, bestLen);
    }
    if (!ret) ret = strdup("");
    return ret;
}
#endif


#if 0
static void fixMinHeap(int* h, int n, int i, int* c, int* ci2hi) {
    int l, r, min, ci, next;
    l = (i << 1) + 1;
    r = l + 1;
    while (l < n) {
        ci = h[i];
        if (r >= n) {
            if (c[ci] > c[h[l]]) {
                ci2hi[h[i] = h[l]] = i;
                ci2hi[h[l] = ci] = l;
            }
            return;
        }
        min = (c[h[r]] <= c[h[l]]) ? r : l;
        if (c[h[min]] < c[h[i]]) {
            next = l + (min != l);
            ci2hi[h[i] = h[next]] = i;
            ci2hi[h[next] = ci] = next;
            i = next;
        } else {
            return;
        }
        l = (i << 1) + 1;
        r = l + 1;
    }
}

//24ms, O(nlg(m)) time, O(m) space
char* minWindow(char* s, char* t) {
    char* ret = NULL;
    int ci, index, i, j, min, bestStart, bestLen, cLeft;

    const int SLEN = (NULL != s) ? strlen(s) : 0;
    const int TLEN = (NULL != t) ? strlen(t) : 0;

    if ((SLEN < TLEN) || (TLEN <= 0)) return strdup("");

    int     ce[MAX_CH];
    int     cebak[MAX_CH];
    int     heap[TLEN];
    int     raw[TLEN];
    int     ci2hi[TLEN];
    int*    ca[MAX_CH];
    int*    cp;

    memset(ce, 0, sizeof(ce[0]) * MAX_CH);
    for (i = 0; i < TLEN; i++) {
        ce[CH2IDX(t[i])] += 1;
        heap[i] = i;
        ci2hi[i] = i;
        #ifdef MY_UNIT_TEST
        raw[i] = -1;
        #endif
    }
    memcpy(cebak, ce, sizeof(cebak[0]) * MAX_CH);
    for (i = 0, cp = raw; i < MAX_CH; i++) {
        if (ce[i]) {
            ca[i] = cp;
            cp += ce[i];
        } else {
            ca[i] = NULL;
        }
    }

    for (i = 0, cLeft = TLEN; i < SLEN; i++) {
        index = CH2IDX(s[i]);
        cp = ca[index];
        if (cp != NULL) { //ch found in T
            if (ce[index] > 0) { // first time found
                cLeft--;
                ce[index] -= 1;
                cp[ce[index]] = i;
                ci = (int)(cp - raw) + ce[index];
            } else {
                ce[index] += 1;
                cp[-ce[index]] = i;
                ci = (int)(cp - raw) - ce[index];
            }
            if (ce[index] == 0) ce[index] = -cebak[index];
            if (cLeft < 0) {
                fixMinHeap(heap, TLEN, ci2hi[ci], raw, ci2hi);
                min = raw[*heap];
                if (i - min + 1 < bestLen) {
                    bestStart = min;
                    bestLen = i - min + 1;
                    #ifdef MY_UNIT_TEST
                    min = s[bestStart + bestLen];
                    s[bestStart + bestLen] = '\0';
                    printf("i %d, bestStart %d, bestLen %d: %s\n", i, bestStart, bestLen, s + bestStart);
                    s[bestStart + bestLen] = min;
                    #endif
                }
            } else if (!cLeft) {
                //Build heap
                for (j = ((TLEN - 2) >> 1); j >= 0; j--) fixMinHeap(heap, TLEN, j, raw, ci2hi);
                min = raw[*heap];
                cLeft = -1;
                bestStart = min;
                bestLen = i - min + 1;
                #ifdef MY_UNIT_TEST
                min = s[bestStart + bestLen];
                s[bestStart + bestLen] = '\0';
                printf("bestStart %d, bestLen %d: %s\n", bestStart, bestLen, s + bestStart);
                s[bestStart + bestLen] = min;
                #endif
            }
            #ifdef MY_UNIT_TEST
            if (cLeft <= 0) {
                printf("(i %3d, ci %3d, hi %3d):%3d", i, ci, ci2hi[ci], 0);
                for (j = 1; j < TLEN; j++) printf("  %3d", j);
                printf("\n");
                printf("%24c%3d", ' ', raw[heap[0]]);
                for (j = 1; j < TLEN; j++) printf(", %3d", raw[heap[j]]);
                printf("\n");
                printf("%24c%3d", ' ', ci2hi[0]);
                for (j = 1; j < TLEN; j++) printf(", %3d", ci2hi[j]);
                printf("\n");
            }
            #endif
        }
    }

    if (cLeft <= 0) {
        ret = strndup(s + bestStart, bestLen);
    }
    if (!ret) ret = strdup("");
    return ret;
}
#endif

typedef struct {
    int*    cq;
    int     cqlen;
    int     cqhead;
    int     cqtail;
    int     cqfull;
    int     hi;
} ChNode;

static void minHeapify(int* h, int n, int hi, ChNode* cha) {
    int hl, hr, hmin;
    int hhi, hval;

    while (hi < n) {
        hhi = h[hi];
        hl = (hi << 1) + 1;
        hr = hl + 1;
        if (hl >= n) return;
        hval = cha[hhi].cq[cha[hhi].cqhead];
        if (hr >= n) {
            if (hval > cha[h[hl]].cq[cha[h[hl]].cqhead]) {
                cha[h[hi] = h[hl]].hi = hi;
                cha[h[hl] = hhi].hi = hl;
            }
            return;
        }

        hmin = (cha[h[hl]].cq[cha[h[hl]].cqhead] < cha[h[hr]].cq[cha[h[hr]].cqhead]) ? hl : hr;
        if (hval > cha[h[hmin]].cq[cha[h[hmin]].cqhead]) {
            cha[h[hi] = h[hmin]].hi = hi;
            cha[h[hmin] = hhi].hi = hmin;
            hi = hmin;
        } else {
            return;
        }
    }
}
//8ms, O(m+n) time, O(n) space
char* minWindow(char* s, char* t) {
    char* ret = NULL;
    int i, j, lastStart, lastLen, bestStart, bestLen, heapLen, cLeft;

    const int SLEN = (NULL != s) ? strlen(s) : 0;
    const int TLEN = (NULL != t) ? strlen(t) : 0;

    if ((SLEN < TLEN) || (TLEN <= 0)) return strdup("");

    ChNode  cha[MAX_CH];
    int     heap[MAX_CH];
    int*    cqbuf = NULL;
    int*    cqbufp;
    ChNode* chp;
    ChNode**hp;

    cqbuf = (int*)malloc(sizeof(int) * TLEN);
    if (!cqbuf) return strdup("");

    memset(cha, 0, sizeof(cha));
    for (i = 0, heapLen = 0; i < TLEN; i++) {
        chp = cha + t[i];
        j = chp->cqlen;
        if (j++ == 0) {
            chp->hi = heapLen;
            heap[heapLen++] = t[i];
        }
        chp->cqlen = j;
    }

    for (i = 0, j = 0, cqbufp = cqbuf; j < heapLen; i++) {
        chp = cha + i;
        lastLen = chp->cqlen;
        if (lastLen > 0) {
            chp->cqhead = 0;
            chp->cqtail = 0;
            chp->cqfull = 0;
            chp->cq = cqbufp;
            cqbufp += lastLen;
            j++;
        }
    }

    for (i = 0, cLeft = TLEN; i < SLEN; i++) {
        chp = cha + s[i];
        j = chp->cqlen;
        if (j <= 0) continue;
        int newTail = chp->cqtail + 1;
        if (newTail >= j) newTail -= j;

        if (!(chp->cqfull)) {
            cLeft--; //See dup chars as new chars, until cqfull becomes true
            if (chp->cqhead == newTail) { //cq Full
                chp->cqfull = 1;
            }
        } else {
            chp->cqhead = newTail; //Move cqhead to current oldest one
        }

        chp->cq[chp->cqtail] = i;
        chp->cqtail = newTail;
        if (!cLeft) {
            //Mark it -1. For one function call, this block will not be run more than once
            cLeft = -1;

            //Build heap
            for (j = ((heapLen - 2) >> 1); j >= 0; j--) minHeapify(heap, heapLen, j, cha);

            //Calculate initial bestLen
            chp = cha + heap[0];
            bestStart = chp->cq[chp->cqhead];
            bestLen = i - bestStart + 1;

            #ifdef MY_UNIT_TEST
            printf("##i %d, bestStart %d ('%c'), bestLen %d, heap:\n",
                i, bestStart, s[bestStart], bestLen);
            for (j = 0; j < heapLen; j++) printf("%4d", j);
            printf("\n");
            for (j = 0; j < heapLen; j++) printf(",%3d", cha[heap[j]].cq[cha[heap[j]].cqhead]);
            printf("\n");
            #endif
        } else if (cLeft < 0) {
            //Fix heap, O(lgN)
            j = chp->hi;
            minHeapify(heap, heapLen, j, cha);

            //Fix bestLen if needed
            chp = cha + heap[0];
            lastStart = chp->cq[chp->cqhead];
            lastLen = i - lastStart + 1;
            if (lastLen < bestLen) {
                bestStart = lastStart;
                bestLen = lastLen;

                #ifdef MY_UNIT_TEST
                printf("&&i %d, bestStart %d ('%c'), bestLen %d, j %d, heap:\n",
                    i, bestStart, s[bestStart], bestLen, j);
                for (j = 0; j < heapLen; j++) printf("%4d", j);
                printf("\n");
                for (j = 0; j < heapLen; j++) printf(",%3d", cha[heap[j]].cq[cha[heap[j]].cqhead]);
                printf("\n");
                #endif
            }
        }
    }

    free(cqbuf);

    if (cLeft < 0) {
        ret = strndup(s + bestStart, bestLen);
    }
    if (!ret) ret = strdup("");
    return ret;
}
