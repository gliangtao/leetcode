/**
Given an array of citations (each citation is a non-negative integer) of a researcher, write a
function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her
N papers have at least h citations each, and the other N − h papers have no more than h citations
each."

For example, given citations = [3, 0, 6, 1, 5], which means the researcher has 5 papers in total and
each of them had received 3, 0, 6, 1, 5 citations respectively. Since the researcher has 3 papers
with at least 3 citations each and the remaining two with no more than 3 citations each, his h-index
is 3.

Note: If there are several possible values for h, the maximum one is taken as the h-index.

Hint:

An easy approach is to sort the array first.
What are the possible values of h-index?
A faster approach is to use extra space.
*/

int hIndex(int* citations, int citationsSize) {
    if (!citations || (citationsSize <= 0)) return 0;
    const int N = citationsSize;
    int hi[N + 1];
    int i, h;
    memset(hi, 0, sizeof(int) * (N + 1));
    for (i = 0; i < N; i++) {
        h = citations[i];
        if (h > N) h = N;
        hi[h]++;
    }
    for (i = N; i > 0; i--) {
        if (hi[i] >= i) return i;
        hi[i - 1] += hi[i];
    }
    return 0;
}
