/*
 * Use the following command to compile & verify
gcc -g -DGLT_UNIT_TEST perfect_square_lines.c
./a.out 4
./a.out 4 5
./a.out 1 16
./a.out 1 30
*/

/**
 * Given all numbers between "start" and "end", print all permutations of the numbers, where all
 * numbers lined up and each pair of adjacent numbers sum up to a perfect square number.
 *
 * For example, f(1, 16):
 * 8, 1, 15, 10, 6, 3, 13, 12, 4, 5, 11, 14, 2, 7, 9, 16
1, 3, 8, 15
2, 7, 14
3, 6, 13
4, 5, 12
5, 4, 11
6, 3, 10
7, 2, 9
8, 1
9, 7, 16
10, 6, 15
11, 5, 14
12, 4, 13
13, 3, 12
14, 2, 11
15, 1, 10
16, 9
 *
 * f(4, 4):
 * 4
 *
 * f(4,5):
 * 4,5
 * 5,4
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>


#ifdef GLT_UNIT_TEST_VERBOSE
#define VDBG(str...)    printf(str)
static void mydbg()     {}
#else
#define VDBG(str...)
#define mydbg()
#endif

#ifdef GLT_UNIT_TEST
int printPerfectSquareLines(int start, int end);
int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int start = atoi(argv[1]);
    int end = atoi(argv[2]);
    int count;
    gettimeofday(&tvStart, NULL);
    count = printPerfectSquareLines(start, end);
    gettimeofday(&tvEnd, NULL);

    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("\nprintPerfectSquareLines(%d, %d): time %d.%06d seconds, total %d perfect square lines\n",
            start, end, ds, dus, count);
    return 0;
}
#endif

// Node structure in the graph
typedef struct GNode {
    int     value;      // Value associate with the node
    int     visited;    // 0 if not visited, 1 if visited
    int     nextSqrt;   // Next square root
    int     elistSize;  // Size of the edge list
    int*    elist;      // Edge list
} GNode;

static void dumpGraph(GNode* nodes, int N) {
    GNode* node = nodes;
    int i, j;
    printf("Dumping graph (%d nodes):\n", N);
    for (i = 0; i < N; i++, node++) {
        printf("%d (nextSqrt %d, elistSize %d): ", node->value, node->nextSqrt, node->elistSize);
        for (j = 0; j < node->elistSize; j++) {
            printf(",%d", nodes[node->elist[j]].value);
        }
        printf("\n");
    }
}

// Modified square root value is upper-round-to sqrt(num)
// Negative if num is not perfect square
static int mySqrt(int num) {
    if (num <= 0) return 0;
    int l, m, r, d;
    // Use binary search Newton method to find the NEXT square root value
    // NOTE: it's NOT the standard square root value
    for (l = 1, r = num; l <= r;) {
        m = ((l + r) >> 1);
        d = m - (num / m);
        if (!d) d = m * m - num;
        if (d < 0) {
            l = m + 1;
        } else if (d > 0) {
            r = m - 1;
        } else {
            return m;
        }
    }
    return -l;
}

// Find next square root whose square value is upper-close-to (2*x + 1)
static int getNextSqrt(int x) {
    int ret = mySqrt(x + x + 1);
    VDBG("getNextSqrt(%d): %d\n", x, (ret < 0) ? (-ret) : ret);
    return (ret < 0) ? (-ret) : ret;
}

// Abort if malloc fails
static inline void* mustMalloc(size_t size) {
    void* ret = malloc(size);
    if (!ret) {
        fprintf(stderr, "Fatal error: out of memory!\n");
        abort();
        exit(-1); // Ensure process is terminated here
    }
    return ret;
}

// Simply free
static inline void mustFree(void* ptr) {
    free(ptr);
}

// Initialize the graph
// Return number of odd nodes, each of which has one or none adjacent node
static int initGraph(GNode* nodes, int start, int end, int N) {
    int min = getNextSqrt(start);
    int max = getNextSqrt(end);
    GNode* node;
    int i, j, nextSqrt = min;
    size_t maxEdgeListSize = sizeof(int) * (max - min + 1);

    for (i = start, node = nodes; i <= end; nextSqrt++) {
        int nextI = (nextSqrt * nextSqrt - 1) >> 1;
        if (nextI > end) nextI = end;
        for (; i <= nextI; i++, node++) {
            node->value = i;
            node->visited = 0;
            node->nextSqrt = nextSqrt;
            node->elistSize = 0;
            node->elist = (int*)mustMalloc(maxEdgeListSize);
        }
    }

    for (i = 0, node = nodes; i < N; i++, node++) {
        for (j = node->nextSqrt; j < max; j++) {
            int k = (j * j) - i - start - start;
            if (k >= N) break;
            node->elist[node->elistSize++] = k;
            GNode* node2 = nodes + k;
            node2->elist[node2->elistSize++] = i;
        }
    }

    int oddNodeCount = 0;
#ifdef GLT_UNIT_TEST_VERBOSE
    dumpGraph(nodes, N);
#endif
    for (i = 0; i < N; i++) {
        if (nodes[i].elistSize <= 1) {
            VDBG("oddNode %d: %d\n", i, nodes[i].value);
            oddNodeCount++;
        }
    }
    VDBG("oddNodeCount %d\n", oddNodeCount);
    return oddNodeCount;
}

// Finalize the graph
static void finiGraph(GNode* nodes, int N) {
    int i;
    for (i = 0; i < N; i++) mustFree(nodes[i].elist);
    mustFree(nodes);
}

// Print the whole trail
static int printTrail(GNode** trail, int N) {
    int i;
    printf("Trail:");
    for (i = 0; i < N; i++) {
        printf(",%d", trail[i]->value);
    }
    printf("\n");
    return 1;
}

// Backtracking traversal of the graph
static int backtrack(GNode* nodes, GNode** trail, int trailPos, GNode* node, int N) {
    if (trailPos >= N) {
        return printTrail(trail, N);
    }

    int ret = 0;
    int i;
    for (i = node->elistSize - 1; i >= 0; i--) {
        GNode* next = nodes + node->elist[i];
        if (next->visited == 0) {
            // Bail quickly if oddNode is found in middle
            if ((trailPos != (N - 1)) && (next->elistSize < 2)) return 0;
            next->visited = 1;
            trail[trailPos] = next;
            ret += backtrack(nodes, trail, trailPos + 1, next, N);
            next->visited = 0;
        }
    }

    return ret;
}

// Return total number of valid perfectSquareLines
int printPerfectSquareLines(int start, int end) {
    int d = end - start;
    if (!d) {
        if ((end >= 0) && (mySqrt(end) >= 0)) {
            GNode dummy;
            GNode* p = &dummy;
            dummy.value = end;
            return printTrail(&p, 1);
        }
        return 0;
    }
    if (d < 0) {
        d = end;
        end = start;
        start = d;
    }
    if (start < 0) {
        return 0;
    }

    const int N = end - start + 1;
    GNode* nodes = (GNode*)mustMalloc(N * sizeof(GNode));
    int ret = 0;

    if (initGraph(nodes, start, end, N) <= 2) {
        int i;
        GNode** trail = (GNode**)mustMalloc(N * sizeof(GNode*));
        for (i = 0; i < N; i++) {
            nodes[i].visited = 1;
            trail[0] = nodes + i;
            ret += backtrack(nodes, trail, 1, nodes + i, N);
            nodes[i].visited = 0;
        }
        mustFree(trail);
    }
    finiGraph(nodes, N);

    return ret;
}
