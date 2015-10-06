char* longestCommonPrefix(char** strs, int strsSize) {
    int i;
    int j = 0;
    int ch;
    if (!strs || !strsSize) {
        return "";
    }
    while (1) {
        ch = strs[0][j];
        if (!ch) {
            break;
        }
        for (i = strsSize - 1; i > 0; i--) {
            if (strs[i][j] != ch) {
                goto my_exit;
            }
        }
        j++;
    }

my_exit:
    return (j > 0) ? strndup(strs[0], j) : "";
}
