#include "ft_printf.h"
/*
**	FUNCTION BELOW IS CALLED BY AN X_PH FUNCTION.
*/
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
/*
**	______________
** 	   OPTIONS
**	______________
** 	0 = c/s
**  1 = d/i/o/u/x/X
**  2 = p
*/

void			prints_alpha(char buff[65], t_flags flags)
{
	int width;
	int len;
	char *pad;

	width = flags.width;
	len = ft_strlen(buff);
	pad = flags.zero && !flags.neg ? zeros : spaces;
	if (width > len)
	{
		if (!flags.neg)
			putpad(pad, width - len);
		write(1, buff, len);
		if (flags.neg)
			putpad(pad, width - len);
	}
	else
	{
		if (flags.precision)
			len = width;
		write(1, buff, len);
	}
}
void			prints_addr(char buff[65], t_flags flags)
{
	int width;
	int len;
	char *pad;

	width = flags.width;
	len = ft_strlen(buff);
	pad = (flags.zero && !flags.neg) || flags.precision ? zeros: spaces;
	if (width > len)
	{
		if (flags.precision)
		{
			write(1, "0x", 2);
			putpad(pad, width - len);
		}
		else if (!flags.neg)
		{ 
			if (flags.zero)
			{
				write(1, "0x", 2);
				putpad(pad, width - len - 2);
			}
			else
			{
				putpad(pad, width - len - 2);
				write(1, "0x", 2);
			}
		}
		if (flags.neg && !flags.precision)
			write(1, "0x", 2);
		write(1, buff, len);
		if (flags.neg && !flags.precision)
		{
			putpad(pad, width - len - 2);
		}
	}
	else
	{
		write(1, "0x", 2);
		write(1, buff, len);
	}
}

void			prints_num(char buff[65], t_flags flags)
{
	int width;
	int len;
	char *pad;

	width = flags.width;
	len = ft_strlen(buff);
	pad = flags.zero ? zeros : spaces ;
	if (width > len)
	{
		putpad(pad, width - len);
	}
}
void			prints_ph(char	buff[65], t_flags flags, int opt)
{
	int		n;
	int		len;
	char	*pad;

	n = flags.width;
	len = ft_strlen(buff);
	pad = flags.zero ? zeros : spaces;
	if (opt == 1 && flags.precision)
		pad = zeros;
	if (!flags.neg && !flags.precision && !flags.zero && n > len)
		putpad(pad, n - len);
	if (opt == 2 && (n -= 2))
		write(1, "0x", 2);
	if (flags.precision && opt == 2)
		putpad(zeros, n - len + 2);
	if (!flags.neg && !flags.precision && n > len)
	{
		if (opt == 1)
			if (buff[0] == '-')
				write(1, buff++, 1);
		putpad(pad, n - len);
	}
	write(1, buff, len);
	if (flags.neg && !flags.precision && n > len)
		putpad(spaces, n - len);
}