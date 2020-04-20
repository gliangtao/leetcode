#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/time.h>

char* strstrKmp(const char* str, const char* pattern);
int main(int argc, char** argv) {
    struct timeval tvStart, tvEnd;
    char* result;
    gettimeofday(&tvStart, NULL);
    result = strstrKmp((const char*)argv[1], (const char*)argv[2]);
    gettimeofday(&tvEnd, NULL);
    int ds = tvEnd.tv_sec - tvStart.tv_sec;
    int dus = tvEnd.tv_usec - tvStart.tv_usec;
    if (dus < 0) {
        ds--;
        dus += 1000000;
    }
    printf("Time %d.%06d, strstrKmp substring: %s\n", ds, dus, result);
    return 0;
}
#if 0
void preKmp(char *x, int m, int kmpNext[]) {
   int i, j;

   i = 0;
   j = kmpNext[0] = -1;
   while (i < m) {
      while (j > -1 && x[i] != x[j])
         j = kmpNext[j];
      i++;
      j++;
      if (x[i] == x[j])
         kmpNext[i] = kmpNext[j];
      else
         kmpNext[i] = j;
   }
}


void KMP(char *x, int m, char *y, int n) {
   int i, j, kmpNext[XSIZE];

   /* Preprocessing */
   preKmp(x, m, kmpNext);

   /* Searching */
   i = j = 0;
   while (j < n) {
      while (i > -1 && x[i] != y[j])
         i = kmpNext[i];
      i++;
      j++;
      if (i >= m) {
         OUTPUT(j - i);
         i = kmpNext[i];
      }
   }
}
#endif
static void preKmp(const char* pattern, int* next, size_t plen) {
   ssize_t i;
   ssize_t j;
   int ch;
   next[0] = -1;

   printf("P:  ");
   for (j = 0; j < plen; j++) {
      printf("   %c", pattern[j]); 
   }
   printf("\nN:    -1");
   j = -1;
   for (i = 1; i < plen; i++) {
      ch = pattern[i];
      while ((j >= 0) && (pattern[j + 1] != ch)) {
         j = next[j];
      }
      if (pattern[j + 1] == ch) {
         j++;
      }
      next[i] = j;
      printf(" %3d", next[i]);
   }
   printf("\n");
}

char* strstrKmp(const char* str, const char* pattern) {
   size_t plen = strlen(pattern);
   int* next = (int*)malloc(sizeof(int) * plen);
   if (next) {
      int ch;
      ssize_t i, j;
      size_t slen = strlen(str);
      j = -1;
      preKmp(pattern, next, plen);
      for (i = 0; i < slen;) {
         ch = str[i];
         while ((j >= 0) && (pattern[j + 1] != ch)) {
            j = next[j];
         }
         i++;
         j++;
         if (j == plen - 1) {
            free(next);
            return (char*)str + i - plen;
            //j = next[j] ==> to get next match
         }
      }
      free(next);
   }
   return NULL;
}
