/*
You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
*/
//0ms version, O(n)
int climbStairs(int n) {
    if (n <= 2) return ((n > 0) ? n : 0);

    const int N = n;
    int i;
    int c[N];
    c[0] = 1;
    c[1] = 2;
    for (i = 2; i < N; i++) {
        c[i] = c[i - 1] + c[i - 2];
    }
    return c[N - 1];
}
