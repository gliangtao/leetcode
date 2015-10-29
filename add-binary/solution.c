/*
Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100".
*/
//0ms version
char* addBinary(char* a, char* b) {
    if (!a || !b) return NULL;

    int alen, blen;
    alen = strlen(a);
    blen = strlen(b);

    int len1, len2;
    char* p1, *p2;
    if (alen <= blen) {
        len1 = alen;
        len2 = blen;
        p1 = a;
        p2 = b;
    } else {
        len1 = blen;
        len2 = alen;
        p1 = b;
        p2 = a;
    }

    int size = len2 + 1 + !!len1;

    char* ret = (char*)malloc(size);
    if (ret) {
        int carry = 0, i;
        char* p;
        ret[0] = '0';

        p1 = p1 + len1 - 1;
        p2 = p2 + len2 - 1;
        p = ret + size - 1;
        *p-- = '\0';
        for (i = 0; i < len1; i++) {
            int d =  *p1 + *p2 - '0' + carry;
            if (d > '1') {
                d -= 2;
                carry = 1;
            } else {
                carry = 0;
            }
            *p-- = d;
            p1--;
            p2--;
        }
        for (; i < len2; i++) {
            int d =  *p2 + carry;
            if (d > '1') {
                d -= 2;
                carry = 1;
            } else {
                carry = 0;
            }
            *p-- = d;
            p2--;
        }
        ret[0] += carry;
        if (len2 && (ret[0] == '0')) {
            char* newret = strdup(ret + 1);
            free(ret);
            ret = newret;
        }
    }
    return ret;
}
