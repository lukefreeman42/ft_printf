#include "ft_printf.h"
#include <stdio.h>
int     main(int argc, char **argv)
{
    char a;
    char *b;

    a = 'h';
    b = "hello";
    if (argc == 4)
    {
        ft_printf(argv[1], a, b);
        write(1,"\n", 1);
        printf(argv[1], a, b);
    }
    return (0);
}