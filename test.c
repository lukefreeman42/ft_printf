#include "ft_printf.h"
#include <stdio.h>
int     main(int argc, char **argv)
{
    char a;
    char *b;
    double f;
    a = 'h';
    b = "hello this should be over 64 bytes we will make sure it is, this is the only way to test forsure about whatever happens to see if my printf works like the standard using buff and no malloc, quick ! speed ! fast ! faster! fastest !";
    f = 1.325;
    if (argc == 2)
    {
        ft_printf(argv[1], &a, f);
        write(1,"\n", 1);
        printf(argv[1], &a, f);
    }
    return (0);
}