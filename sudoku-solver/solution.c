
#if 0
//4ms version
/*
#define GET(a, v1, v2, v3)      ((a[v2] & (1 << (v3 + (v1 * 9)))))
#define SET(a, v1, v2, v3)      ((a[v2] |= (1 << (v3 + (v1 * 9)))))
#define CLR(a, v1, v2, v3)      ((a[v2] &= ~(1 << (v3 + (v1 * 9)))))
*/
#define BIT0                (1)
#define BIT1                (1 << 9)
#define BIT2                (1 << 18)

#define GET0(a, v1, v2)     (a[v1] & (BIT0 << v2))
#define SET0(a, v1, v2)     (a[v1] |= (BIT0 << v2))
#define CLR0(a, v1, v2)     (a[v1] &= ~(BIT0 << v2))

#define GET1(a, v1, v2)     (a[v1] & (BIT1 << v2))
#define SET1(a, v1, v2)     (a[v1] |= (BIT1 << v2))
#define CLR1(a, v1, v2)     (a[v1] &= ~(BIT1 << v2))

#define GET2(a, v1, v2)     (a[v1] & (BIT2 << v2))
#define SET2(a, v1, v2)     (a[v1] |= (BIT2 << v2))
#define CLR2(a, v1, v2)     (a[v1] &= ~(BIT2 << v2))

static int DFS(char** board, uint32_t a[9], int i, int j) {
    if (board[i][j] == '.') {
        int k = ((3 * (i / 3)) + (j / 3));
        int m, n;
        for (int c = 0; c < 9; c++) {
            if (GET0(a, i, c) || GET1(a, j, c) || GET2(a, k, c)) continue;
            SET0(a, i, c);
            SET1(a, j, c);
            SET2(a, k, c);
            board[i][j] = c + '1';
            m = i;
            n = j + 1;
            if (n == 9) {
                if (++m == 9) return 1;
                n = 0;
            }
            if (DFS(board, a, m, n)) return 1;
            board[i][j] = '.';
            CLR0(a, i, c);
            CLR1(a, j, c);
            CLR2(a, k, c);
        }
        return 0;
    } else {
        if (++j == 9) {
            if (++i == 9) return 1;
            j = 0;
        }
        return DFS(board, a, i, j);
    }
}

void solveSudoku(char** board, int boardRowSize, int boardColSize) {
    if (!board || (boardRowSize != 9) || (boardColSize != 9)) {
        return;
    }
    uint32_t a[9] = { 0 };
    for (unsigned int i = 0; i < 9; i++) {
        for (unsigned int j = 0; j < 9; j++) {
            unsigned int c = (unsigned int)(board[i][j] - '1');
            if (c <= 9) {
                int k = (3 * (i / 3)) + (j / 3);
                SET0(a, i, c);
                SET1(a, j, c);
                SET2(a, k, c);
            }
        }
    }
    DFS(board, a, 0, 0);
}
#endif

//Another 4ms version
#define GET(a, v1, v2, v3)      (a[v1][v2] & (1 << v3))
#define SET(a, v1, v2, v3)      (a[v1][v2] |= (1 << v3))
#define CLR(a, v1, v2, v3)      (a[v1][v2] &= ~(1 << v3))

static int DFS(char** board, int a[3][9], int i, int j) {
    if (i == 9) return 1;
    if (board[i][j] == '.') {
        int k = ((3 * (i / 3)) + (j / 3));
        int m, n;
        for (int c = 0; c < 9; c++) {
            if (GET(a, 0, i, c) || GET(a, 1, j, c) || GET(a, 2, k, c)) continue;
            SET(a, 0, i, c);
            SET(a, 1, j, c);
            SET(a, 2, k, c);
            board[i][j] = c + '1';
            m = i;
            n = j + 1;
            if (n == 9) {
                m++;
                n = 0;
            }
            if (DFS(board, a, m, n)) return 1;
            board[i][j] = '.';
            CLR(a, 0, i, c);
            CLR(a, 1, j, c);
            CLR(a, 2, k, c);
        }
        return 0;
    } else {
        if (++j == 9) {
            i++;
            j = 0;
        }
        return DFS(board, a, i, j);
    }
}
//4ms version
void solveSudoku(char** board, int boardRowSize, int boardColSize) {
    if (!board || (boardRowSize != 9) || (boardColSize != 9)) {
        return;
    }
    int a[3][9];
    memset(a, 0, sizeof(a));
    for (unsigned int i = 0; i < 9; i++) {
        for (unsigned int j = 0; j < 9; j++) {
            unsigned int c = (unsigned int)(board[i][j] - '1');
            if (c < 9) {
                int k = (3 * (i / 3)) + (j / 3);
                SET(a, 0, i, c);
                SET(a, 1, j, c);
                SET(a, 2, k, c);
            }
        }
    }
    DFS(board, a, 0, 0);
}

//NOTE: please refer to https://leetcode.com/discuss/59649/yet-another-0ms-c-solution
