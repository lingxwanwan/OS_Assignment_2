#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    // make a counterm which counts from 0 to 2^32-1
    long i = 0;
    while (i < pow(2, 32) - 1)
    {
        i++;
    }
    printf("%ld", i);
    return 0;
}
