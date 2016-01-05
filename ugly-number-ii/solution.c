/**
Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example,
1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.

Note that 1 is typically treated as an ugly number.

Hint:

The naive approach is to call isUgly for every number until you reach the nth one. Most numbers
are not ugly. Try to focus your effort on generating only the ugly ones.
An ugly number must be multiplied by either 2, 3, or 5 from a smaller ugly number.
*/
//4ms version
int nthUglyNumber(int n) {
    const int N = n;
    int ugly[N];
    int last, i, n2, n3, n5, i2, i3, i5;
    i2 = i3 = i5 = 0;
    for (i = 0; i < n; i++) ugly[i] = 1;
    for (i = last = n2 = n3 = n5 = 1; i < n;) {
        if (n2 <= last) n2 = (ugly[i2++] << 1);
        if (n3 <= last) n3 = (ugly[i3++] * 3);
        if (n5 <= last) n5 = (ugly[i5++] * 5);
        ugly[i++] = last = ((n2 < n3) ? ((n2 < n5) ? n2 : n5) : ((n3 < n5) ? n3 : n5));
    }
    return last;
}
