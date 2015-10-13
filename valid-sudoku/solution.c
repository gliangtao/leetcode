
#define N           9
#define C2IDX(c)    ((unsigned int)(c - '0'))
//4ms version
bool isValidSudoku(char** board, int boardRowSize, int boardColSize) {
    int a[N];
    int i, j;
    int count = 0;
    char* p;
    unsigned int idx;
    if (!board || (boardRowSize != 9) || (boardColSize != 9)) {
        return false;
    }
    for (i = 0; i < N; i++) a[i] = count;
    count++;
    for (i = 0; i < N; i++) {
        p = board[i];
        for (j = 0; j < N; j++) {
            idx = C2IDX(p[j]);
            if (idx <= N) {
                if (a[idx] != count) {
                    a[idx] = count;
                } else {
                    return false;
                }
            }
        }
        count++;
    }

    for (j = 0; j < N; j++) {
        for (i = 0; i < N; i++) {
            p = board[i];
            idx = C2IDX(p[j]);
            if (idx <= N) {
                if (a[idx] != count) {
                    a[idx] = count;
                } else {
                    return false;
                }
            }
        }
        count++;
    }
    int m, n;
    for (i = 0; i < N; i += 3) {
        for (j = 0; j < N; j += 3) {
            for (m = 0; m < 3; m++) {
                p = board[i + m];
                for (n = 0; n < 3; n++) {
                    idx = C2IDX(p[j + n]);
                    if (idx <= N) {
                        if (a[idx] != count) {
                            a[idx] = count;
                        } else {
                            return false;
                        }
                    }
                }
            }
            count++;
        }
    }
    return true;
}
