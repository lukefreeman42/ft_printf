#include "ft_printf.h"
static	void	putpad(char pad[16], int a)
{
	int	div;
	int	mod;

    if (a > 0)
    {
	    div = a / 16;
	    mod = a % 16;
	    while (div--)
	    	write(1, pad, 16);
	    write(1, pad, mod);
    }
}
