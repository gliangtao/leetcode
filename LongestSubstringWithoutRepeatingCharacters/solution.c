#ifdef MY_UNIT_TEST
#include <stdio.h>
#include <string.h>

int lengthOfLongestSubstring(char* s);
int main(int argc, char** argv)
{
    printf("%d\n", lengthOfLongestSubstring(argv[1]));
    return 0;
}
#endif

int lengthOfLongestSubstring(char* s) {
    int maxLen = -1;
    char* flags[256];
    char* p;
    char* q;
    char* pStart;
    int len;
    int ch;
    int i;
    if (!s) {
        return 0;
    }
    i = 0;
    pStart = s;
    p = s;
    memset(flags, 0, sizeof(flags));
    while ((ch = *p) != 0) {
        if (flags[ch] >= pStart) {
            len = p - pStart;
            if (maxLen < len) {
                maxLen = len;
            }
            pStart = flags[ch] + 1;
        }
        flags[ch] = p++;
    }
    len = p - pStart;
    if (maxLen < len) {
        maxLen = len;
    }
    return maxLen;
}
