#include "ft_printf.h"
#include <stdio.h>
int     main(int argc, char **argv)
{
    long long b = 231464636366;
	char *c = "yes";
    void *a = &b;
    {
        ft_printf(argv[1], b);
        write(1,"\n", 1);
        printf(argv[1], b);
    }
    return (0);
}
