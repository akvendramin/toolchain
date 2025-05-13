#include "main.h"

int main(int ArgumentCount, char **Argument)
{
    int Result = 1;

    Print("%% Hello, world! %%\n");
    Print("%% Hello, world! %%\n");
    Print("%% Hello, world! %%\n");

    Print("%c %c %c\n", 'A', 'B', 'C');
    Print("%c %c %c\n", 'A', 'B', 'C');
    Print("%c %c %c\n", 'A', 'B', 'C');

    Print("%d %i %d\n", 0, -1, 1234);
    Print("%d %i %d\n", 0, -1, 1234);
    Print("%d %i %d\n", 0, -1, 1234);

    Print("%f %f %f\n", 0.0, 0.1, 1.234);
    Print("%f %f %f\n", 0.0, 0.1, 1.234);
    Print("%f %f %f\n", 0.0, 0.1, 1.234);

    Print("%lld %lli\n", 0x7FFFFFFFFFFFFFFF, 0x7FFFFFFFFFFFFFFF);
    Print("%lld %lli\n", 0x7FFFFFFFFFFFFFFF, 0x7FFFFFFFFFFFFFFF);
    Print("%lld %lli\n", 0x7FFFFFFFFFFFFFFF, 0x7FFFFFFFFFFFFFFF);

    Print("%llu\n", 0xFFFFFFFFFFFFFFFF);
    Print("%llu\n", 0xFFFFFFFFFFFFFFFF);
    Print("%llu\n", 0xFFFFFFFFFFFFFFFF);

    Print("%o %o %o\n", 0, 8, 16);
    Print("%o %o %o\n", 0, 8, 16);
    Print("%o %o %o\n", 0, 8, 16);

    Print("%p %p %p\n", 0, main, Argument);
    Print("%p %p %p\n", 0, main, Argument);
    Print("%p %p %p\n", 0, main, Argument);

    Print("%s %s %s\n", "ABC", "DEF", "GHI");
    Print("%s %s %s\n", "ABC", "DEF", "GHI");
    Print("%s %s %s\n", "ABC", "DEF", "GHI");

    Print("%u %u %u\n", 0, -1, 1234);
    Print("%u %u %u\n", 0, -1, 1234);
    Print("%u %u %u\n", 0, -1, 1234);

    Print("%x %X %x\n", 0, -1, 255);
    Print("%x %X %x\n", 0, -1, 255);
    Print("%x %X %x\n", 0, -1, 255);

    return 0;
}