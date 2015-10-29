/*
Given a string s consists of upper/lower-case alphabets and empty space characters ' ',
return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

For example, 
Given s = "Hello World",
return 5.
*/
//0ms version
int lengthOfLastWord(char* s) {
    if (!s || !*s) return 0;
    char* end = s + strlen(s) - 1;
    char *q, *p;
    int ch;
    for (q = end; q >= s; q--) {
        if (*q != ' ') {
            for (p = q - 1; p >= s; p--) {
                if (*p == ' ') break;
            }
            return (int)(q - p);
        }
    }

    return 0;
}
