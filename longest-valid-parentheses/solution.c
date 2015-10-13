#if 0
//8ms version
/**
 * Given a string containing just the characters '(' and ')', find the length of the longest valid
 * (well-formed) parentheses substring.
 *
 * For "(()", the longest valid parentheses substring is "()", which has length = 2.
 *
 * Another example is ")()())", where the longest valid parentheses substring is "()()",
 * which has length = 4.
 */
int longestValidParentheses(char* s) {
    char *p;
    int nl, nr, ch, maxHalf = 0;

    if (!s) {
        return 0;
    }

    for (p = s - 1, nl = nr = 0;;) {
        ch = *(++p);
        if ('(' == ch) {
            nl++;
            continue;
        } else if ((')' == ch) && (nr < nl)) {
            nr++;
            continue;
        }
        if (nl == nr) {
            if (maxHalf < nr) maxHalf = nr;
        } else if (maxHalf < nr) {
            char* limit = p - nl - nr;
            char* q = p - 1;
            int ch2;
            nl = nr = 0;
            while (q >= limit) {
                ch2 = *q--;
                if (')' == ch2) {
                    nr++;
                    continue;
                } else if (('(' == ch2) && (nl < nr)) {
                    nl++;
                    continue;
                }
                if (maxHalf < nl) maxHalf = nl;
                nl = nr = 0;
            }
            if (maxHalf < nl) maxHalf = nl;
        }
        if (!ch) {
            break;
        }
        nl = nr = 0;
    }
    return (maxHalf << 1);
}
#endif
//0ms version
int longestValidParentheses(char* s) {
    char *p;
    int nl, nr, ch, maxHalf = 0;

    if (!s) {
        return 0;
    }

    for (p = s - 1, nl = nr = 0;;) {
        ch = *(++p);
        if ('(' == ch) {
            nl++;
            continue;
        } else if ((nr < nl) && (')' == ch)) {
            nr++;
            continue;
        }
        if (nl == nr) {
            if (maxHalf < nr) maxHalf = nr;
        } else if (maxHalf < nr) {
            char* limit = p - nl - nr;
            char* q = p - 1;
            nl = nr = 0;
            while (q >= limit) {
                if (')' == *q--) {
                    nr++;
                    continue;
                } else if (nl < nr) {
                    nl++;
                    continue;
                }
                if (maxHalf < nl) maxHalf = nl;
                nl = nr = 0;
            }
            if (maxHalf < nl) maxHalf = nl;
        }
        if (!ch) {
            break;
        }
        nl = nr = 0;
    }
    return (maxHalf << 1);
}
