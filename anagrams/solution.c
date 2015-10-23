
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

char*** groupAnagrams(char** strs, int strsSize, int** columnSizes, int* returnSize);

char* N[] =
//{ "", "b" };
//{ "eat", "ate", "tea", "nat", "bat" };
//{NULL, "", ""};
{"h","h","h"};

int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int retSize;
    int* colSizes;
    gettimeofday(&tvStart, NULL);
    groupAnagrams(N, sizeof(N) / sizeof(N[0]), &colSizes, &retSize);
    gettimeofday(&tvEnd, NULL);

    printf("groupAnagrams: %d\n", retSize);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    DBG("Time %d.%06d, groupAnagrams\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif

/*
Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"], 
Return:

[
  ["ate", "eat","tea"],
  ["nat","tan"],
  ["bat"]
]
Note:
For the return value, each inner list's elements must follow the lexicographic order.
All inputs will be in lower-case.
Update (2015-08-09):
The signature of the function had been updated to return list<list<string>> instead of list<string>,
as suggested here. If you still see your function signature return a list<string>, please click the
* reload button  to reset your code definition.
*/

#include <stdlib.h>
#include <string.h>

typedef struct {
    char*   str;
    int*    charmap;
    int     len;
} MyItem;

typedef struct {
    char**  start;
    int     size;
} MySet;

typedef struct {
    char**  strs;
    int*    charmaps;
    MyItem* items;
    MySet*  sets;
    MyItem**ipa;
} MyContext;

static int mycmp(const void* param1, const void* param2) {
    MyItem* p1 = *((MyItem**)param1);
    MyItem* p2 = *((MyItem**)param2);
    int d;

    if ((d = p1->len - p2->len) != 0) return d;

    int* cm1 = p1->charmap;
    int* cm2 = p2->charmap;
    if (p1->str == p2->str) {
        if (cm1 != cm2) {
            if (p1 < p2) {
                p1->charmap = cm2; // Merge 2 equal charmaps into 1 charmap
            } else {
                p2->charmap = cm1; // Merge 2 equal charmaps into 1 charmap
            }
        }
        return 0; //If str ptr is same, the 2 strings must be equal
    }

    if (cm1 != cm2) {
        for (int i = 26 - 1; i >= 0; i--) {
            if ((d = cm1[i] - cm2[i]) != 0) return d;
        }

        if (p1 < p2) {
            p1->charmap = cm2; // Merge 2 equal charmaps into 1 charmap
        } else {
            p2->charmap = cm1; // Merge 2 equal charmaps into 1 charmap
        }
    }
    return strcmp(p1->str, p2->str);
}

static void initItem(MyItem* pItem) {
    char* p = pItem->str;
    if (!p || !(*p)) {
        pItem->charmap = NULL;
        pItem->len = 0;
    } else {
        //Note: charmap is already initialized to all-0
        int* charmap = pItem->charmap;
        int ch;
        while ((ch = *p) != 0) {
            charmap[ch - 'a'] += 1;
            p++;
        }
        pItem->len = (int)(p - pItem->str);
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
//28ms version
char*** groupAnagrams(char** strs, int strsSize, int** columnSizes, int* returnSize) {
    char*** ret = NULL;
    int     retSize = 0;
    int*    colSizes = NULL;

    MyContext ctx;

    ctx.strs = (char**)malloc(sizeof(char*) * strsSize);
    ctx.charmaps = (int*)malloc(sizeof(int) * 26 * strsSize);
    ctx.items = (MyItem*)malloc(sizeof(MyItem) * strsSize);
    ctx.sets = (MySet*)malloc(sizeof(MySet) * strsSize);
    ctx.ipa = (MyItem**)malloc(sizeof(MyItem*) * strsSize);

    if (!strs || !strsSize || !ctx.strs || !ctx.charmaps || !ctx.items || !ctx.sets || !ctx.ipa)
        goto bail;

    memset(ctx.charmaps, 0, sizeof(int) * 26 * strsSize);

    int i;
    char**  pp = strs;
    MyItem* pItem = ctx.items;
    MyItem** pip = ctx.ipa;
    int* pcharmap = ctx.charmaps;
    for (i = 0; i < strsSize; i++) {
        pItem->str = *pp++;
        pItem->charmap = pcharmap;
        initItem(pItem);

        pcharmap += 26;
        *pip++ = pItem++;
    }

    qsort(ctx.ipa, strsSize, sizeof(MyItem*), mycmp);

    int lastSetEndIdx = 0;
    MyItem *p1, *p2;
    MySet* pSet = ctx.sets;
    pip = ctx.ipa;
    ctx.strs[0] = (pip[0]->str);
    for (i = 1, p1 = *pip; i < strsSize; i++) {
        p2 = *(++pip);
        ctx.strs[i] = (p2->str);
        if (p1->charmap != p2->charmap) {
            //(p1->len != p2->len) || (p1->charmap != p2->charmap)
            // "Got new set between lastSetEndPtr and pip";
            pSet->start = ctx.strs + lastSetEndIdx;
            pSet->size = i - lastSetEndIdx;
            pSet++;
            lastSetEndIdx = i;
        }
        p1 = p2;
    }

    pSet->start = ctx.strs + lastSetEndIdx;
    pSet->size = i - lastSetEndIdx;
    pSet++;

    retSize = (int)(pSet - ctx.sets);
    ret = (char***)malloc(sizeof(char**) * retSize);
    colSizes = (int*)malloc(sizeof(int) * retSize);
    if (ret && colSizes) {
        char*** ppp = ret;
        int* pColSize = colSizes;
        for (i = 0; i < retSize; i++) {
            char** buf = (char**)malloc(sizeof(char*) * ctx.sets[i].size);
            if (buf) memcpy(buf, ctx.sets[i].start, sizeof(char*) * ctx.sets[i].size);
            *ppp++ = buf;
            *pColSize++ = ctx.sets[i].size;
            #ifdef MY_UNIT_TEST
            printf("Set %d:", i);
            for (int j = 0; j < ctx.sets[i].size; j++) {
                printf(",'%s'", ppp[-1][j]);
            }
            printf("\n");
            #endif
        }
    } else {
        free(ret);
        free(colSizes);
        ret = NULL;
        colSizes = NULL;
    }

bail:
    if (returnSize) *returnSize = retSize;
    if (columnSizes) {
        *columnSizes = colSizes;
    } else {
        free(colSizes);
    }
    free(ctx.strs);
    free(ctx.charmaps);
    free(ctx.items);
    free(ctx.sets);
    free(ctx.ipa);
    #ifdef MY_UNIT_TEST
    printf("%s returning %p, retSize %d\n", __FUNCTION__, ret, retSize);
    #endif
    return ret;
}
