/**
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a
non-empty word in str.

Examples:
pattern = "abba", str = "dog cat cat dog" should return true.
pattern = "abba", str = "dog cat cat fish" should return false.
pattern = "aaaa", str = "dog cat cat dog" should return false.
pattern = "abba", str = "dog dog dog dog" should return false.
Notes:
You may assume pattern contains only lowercase letters, and str contains lowercase letters separated
by a single space.
*/

#if 1
#include <string.h>
static char* mystrchrnul(char* str, int c) {
    while (*str && (*str != c)) str++;
    return str;
}

static int myintcmp(const void* p1, const void* p2) {
    return (*((int*)p1) - *((int*)p2));
}

bool wordPattern(char* pattern, char* str) {
    if (!pattern || !str) return true;
    const int N = strlen(pattern);
    if (!N && *str) return false;
    int count[26];
    int stridx[N];
    int cmapptn[26];
    int cmapstr[26];
    int i, idx, t, j;
    char* pstr, *qstr;
    for (i = 0, pstr = str; i < N; i++) {
        qstr = mystrchrnul(pstr, ' ');
        t = *qstr;
        *qstr = '\0';
        //printf("i %d, N %d, t '%c', pstr %d '%s'\n", i, N, t, (int)(pstr - str), pstr);
        if ((!t && (i < N - 1)) || (t && (i == (N - 1)))) {
            return false;
        }
        stridx[i] = (int)(str - strstr(str, pstr)) - 1;
        *qstr = t;
        pstr = qstr + 1;
    }
    for (i = idx = 0; i < N; i++) {
        if ((t = stridx[i]) < 0) {
            if (idx >= 26) {
                printf("idx %d >= 26!!!\n", idx);
                return false;
            }
            for (j = i; j < N; j++) {
                if (stridx[j] == t) stridx[j] = idx;
            }
            idx++;
        }
    }
    /**
    printf("stridx:");
    for (i = 0; i < N; i++) {
        printf("%c", stridx[i] + 'a');
    }
    printf("\n");
    */
    memset(cmapptn, 0, sizeof(int) * 26);
    memset(cmapstr, 0, sizeof(int) * 26);
    for (i = 0; i < N; i++) {
        cmapptn[pattern[i] - 'a'] += 1;
        cmapstr[stridx[i]] += 1;
    }
    qsort(cmapptn, 26, sizeof(int), myintcmp);
    qsort(cmapstr, 26, sizeof(int), myintcmp);
    return !memcmp(cmapptn, cmapstr, 26 * sizeof(int));
}
#else
bool wordPattern(char* pattern, char* str)
{
    int i, j, len = strlen(pattern);
    int search[len];
    char *token, *saveptr; char strtmp[strlen(str) + 1];
    for(i = 0; i < len; i++) search[i] = -1;

    strcpy(strtmp, str);
    token = strtok_r(strtmp, " ", &saveptr);
    for(i = 0; i < len; i++) {
        int a = strchr(pattern, pattern[i]) - pattern;

        if(token == NULL) break;
        int b = strstr(str, token) - str;

        for(j = 0; j < a; j++)
                if(search[j] == b) return false;
        if(search[a] == -1) search[a] = b;
        else if(search[a]!= b) return false;
        token = strtok_r(NULL, " ", &saveptr);
    }
    if((token == NULL) ^ (i== len)) return false;
    return true;
}
#endif
