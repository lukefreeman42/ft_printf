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

void			prints_alpha(char buff[65], t_flags flags, int len)
{

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