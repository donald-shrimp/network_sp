#include <stdio.h>
#include <string>
int main()
{
    unsigned long num = 0;

    for (unsigned long i = 1; i <= 1000000000; i++)
    {
        num = num + i;
    }
    printf("num:%ld\n", num);
}
