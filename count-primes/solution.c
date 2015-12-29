/**
Count the number of prime numbers less than a non-negative number, n.
*/
static int getSqrt(int n) {
    int l, r, m, d;
    for (l = 1, r = n; l <= r;) {
        m = ((l + r) >> 1);
        d = m - (n / m);
        if (!d) d = m * m - n;
        if (d < 0) l = m + 1;
        else if (d > 0) r = m - 1;
        else return m;
    }
    return r;
}

int countPrimes(int n) {
    if (n < 2) return 0;
    if (n < 4) return (n - 2);
    int nsqrt = getSqrt(n);
    char* notPrime = (char*)calloc(n - 2, 1);
    int i, j;
    for (i = 2; i <= nsqrt; i++) {
        if (!notPrime[i - 2]) {
            for (j = i * i; j < n; j += i) notPrime[j - 2] = 1;
        }
    }
    for (i = j = 0; i < n - 2; i++) if (!notPrime[i]) j++;
    free(notPrime);
    return j;
}
