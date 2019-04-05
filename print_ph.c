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
    char *x;
    int len;
    char *pad;

    len = ft_strlen(b);
    pad = (op.precision || op.zero) ? g_zeros : g_spaces;
    x = b[0] == '-' ? "-" : op.add ? "+" : op.space ? " " : op.alt ? op.plhld == 'o' ? "0" : op.plhld == 'x' ? "0x" : "0X" : "Err";
    if (((op.add || op.space) && b[0] != '-' && op.width--) || (b[0] == '-' && b++ && op.precision && len--) 
		|| (op.plhld == 'o' && !op.precision && op.width--) || (op.alt && op.plhld != 'o' && x != NULL && *x != '-' && !op.precision && (op.width -= 2)))
        ;
    if(pad == g_zeros && (op.add || op.space || *x == '-' || *x == '0'))
            write(1, x, ft_strlen(x));
    if (!op.neg)
        putpad(pad, op.width - len);
    if(pad == g_spaces && (op.add || op.space || *x == '-' || *x == '0'))
        write(1, x, ft_strlen(x));
    write(1, b, len);
    if (op.neg)
        putpad(pad, op.width - len);
}

void			prints_alpha(char b[65], t_flags op)
{
	int len;
	char *pad;
	len = ft_strlen(b);
	pad = op.zero ? g_zeros : g_spaces;
	if (op.precision)
	{
		len = len >= op.width ? op.width : len;
		write(1, b, len);
	}
	else
	{
		if(!op.neg)
			putpad(pad, op.width - len);
		write(1, b, len);
		if(op.neg)
			putpad(pad, op.width - len);
	}
}

void		prints_float(char b[65], t_flags op) //prints the buffer based on float rules
{
	int width;
	int int_len;
	int frac_len;
	char *pad;

	width = 0;
	int_len = 0;
	frac_len = 7;
	while (b[width++] != '.')
		int_len++;
	width = op.width;
	pad = (op.precision || op.zero) ? g_zeros : g_spaces;
	if (op.precision && width)
		write(1, b, width + int_len + 1); //rounding func which changes buff based on last digit printed.
	else if (op.precision)
		write(1, b, int_len);
	else if (!op.precision)
	{
		if (!op.neg)
			putpad(pad, width - int_len - frac_len);
		write(1, b, int_len + frac_len);
		if (op.neg)
			putpad(pad, width - int_len - frac_len);
	}
}
