#include "ft_printf.h"
#include <stdio.h>
int     main(int argc, char **argv)
{
    float b = 23.666666;
    long long d = -23456;
	char *c = "yes";
    void *a = &b;
    {
        ft_printf(argv[1], d);
        write(1,"\n", 1);
        printf(argv[1], d);
    }
    return (0);
}
