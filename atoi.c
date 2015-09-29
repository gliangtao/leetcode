#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    printf("atoi(%s) == %d\n", argv[1], atoi(argv[1]));
    return 0;
}
