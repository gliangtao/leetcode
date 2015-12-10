//0ms, O(n) time, O(1) space
void reverseWords(char *s) {
    if (!s || !*s) return;
    char *pl, *pr, *pl1, *pr1;
    int t, roff;

    for (pl = pr = s; *pr == ' '; pr++);
    if (!*pr) {
        *pl = '\0';
        return;
    }
    *pl++ = *pr++;

    for (; (t = *pr) != '\0'; pr++) {
        if ((t != ' ') || (pl[-1] != ' ')) {
            if (pl != pr) {
                *pl = *pr;
            }
            pl++;
        }
    }
    if (pl[-1] != ' ') {
        *pl = '\0';
    } else {
        *(--pl) = '\0';
    }

    pr = pl - 1;
    char* end = pr;

    for (pl = s, pr = end; pl <= pr; pl++, pr--) {
        t = *pl;
        *pl = *pr;
        *pr = t;
    }

    for (pl = s, pr = strchrnul(pl, ' ') - 1; (*pl != '\0');) {
        for (pl1 = pl, pr1 = pr; pl1 <= pr1; pl1++, pr1--) {
            t = *pl1;
            *pl1 = *pr1;
            *pr1 = t;
        }
        pl = pr + 1;
        while (*pl == ' ') pl++;
        pr = strchrnul(pl, ' ') - 1;
    }
}
