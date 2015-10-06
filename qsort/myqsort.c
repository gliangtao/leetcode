#include <stdlib.h>


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>
#ifdef MY_UNIT_TEST

int NA[] = { -4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6 };
//int NA[] = { 0, 2, 1, -3 };
//int NA[] = { -3,-2,-5,3,-4 };
//int NA[] = { 1,2,4,8,16,32,64,128 };

#define DBG(str...) printf(str)
static int mycmp(const void* p1, const void* p2) {
    return (*((int*)p1) - *((int*)p2));
}

void myqsort(void* base, size_t nel, size_t width, int (*compar)(const void*, const void*));
int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    int retSize;
    DBG("Origin nums:");
    for (int i = 0; i < sizeof(NA) / sizeof(NA[0]); i++) {
        DBG(",%d", NA[i]);
    }
    DBG("\n");
    gettimeofday(&tvStart, NULL);
    myqsort(NA, sizeof(NA) / sizeof(NA[0]), sizeof(NA[0]), mycmp);
    gettimeofday(&tvEnd, NULL);
    DBG("Sorted nums:");
    for (int i = 0; i < sizeof(NA) / sizeof(NA[0]); i++) {
        DBG(",%d", NA[i]);
    }
    DBG("\n");
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    DBG("Time %d.%06d, myqsort\n", ds, dus);
    return 0;
}
static void breakme() {}
#else
#define breakme()
#define DBG(str...)
#endif


void myqsort(void* base, size_t nel, size_t width, int (*compar)(const void*, const void*)) {
    if (nel > 2) {
        void *p, *q, *r, *end;
        char tmp[width];
        p = base;
        q = p + (nel >> 1) * width;
        end = base + (nel - 1) * width;
        
        DBG("Old nums 1:");
        for (int i = 0; i < nel; i++) {
            DBG(",%d", ((int*)base)[i]);
        }
        DBG("\n");
        DBG("q %ld (%d)\n", ((q - base) / width), ((int*)q)[0]);
        //p = base - width;
        for (r = end; p < r; r -= width) {
            DBG("AA, r %ld (%d)\n", ((r - base) / width), ((int*)r)[0]);
            if (r == q) {
                continue;
            }
            if (compar(r, q) < 0) {
                while ((p < r) && ((p == q) || (compar(p, q) < 0))) {
                    p += width;
                }
                if (p >= r) {
                    break;
                }
                memcpy(tmp, r, width);
                memcpy(r, p, width);
                memcpy(p, tmp, width);
                p += width;
                if (p == q) {
                    p += width;
                }
            }
        }

        int cmp = compar(p, q);
        if (cmp != 0) {
            if (cmp < 0) {
                if (p < q) {
                    p += width;
                }
            } else {
                if (p > q) {
                    p -= width;
                }
            }
            if (p != q) {
                memcpy(tmp, p, width);
                memcpy(p, q, width);
                memcpy(q, tmp, width);
            }
        }

        DBG("New nums 2:");
        for (int i = 0; i < nel; i++) {
            DBG(",%d", ((int*)base)[i]);
        }
        DBG("\n");
        DBG("p %ld (%d), r %ld (%d)\n", ((p - base) / width), ((int*)p)[0], ((r - base) / width), ((int*)r)[0]);
        if (p > base + width) {
            myqsort(base, ((p - base) / width), width, compar);
        }
        if (p < end - width) {
            myqsort(p + width, nel - 1 - ((p - base) / width), width, compar);
        }
    } else if (nel == 2) {
        DBG("Old nums 3:");
        for (int i = 0; i < nel; i++) {
            DBG(",%d", ((int*)base)[i]);
        }
        DBG("\n");
        if (compar(base, base + width) > 0) {
            char tmp[width];
            memcpy(tmp, base, width);
            memcpy(base, base + width, width);
            memcpy(base + width, tmp, width);
        }
        DBG("New nums 3:");
        for (int i = 0; i < nel; i++) {
            DBG(",%d", ((int*)base)[i]);
        }
        DBG("\n");
    }
}
