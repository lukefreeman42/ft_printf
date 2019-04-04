#include "ft_printf.h"
static	void	putpad(char pad[16], int a)
{
	int	div;
	int	mod;

	div = a / 16;
	mod = a % 16;
	while (div--)
		write(1, pad, 16);
	write(1, pad, mod);
}
void        prints_num2(char b[65], t_flags op)
{
    if (op.neg)
        op.zero = 0;
    if (op.precision)
        op.neg = 0;
    if (op.add)
        op.space = 0;
    char x;

    x = b[0] == '-' ? '-' : op.add ? '+' : ' ';
    if (op.width > ft_strlen(b))
    {
        if (op.precision || op.zero)
        {
            if(op.add || op.space)
                write(1, &x, 1);
            putpad(g_zeros, op.width - ft_strlen(b));
        }
        else
        {
            putpad(g_spaces, op.width - ft_strlen(b));
            if(op.add || op.space)
                write(1, &x, 1);
        }
        write(1, b, ft_strlen(b));
    }
    else
    {
        if(op.add || op.space)
            write(1, &x, 1);
        if (op.precision)
            write(1, b, op.width);
        else
            write(1, b, ft_strlen(b));
    }
}