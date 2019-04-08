/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_alpha.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelias <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:14:24 by llelias           #+#    #+#             */
/*   Updated: 2019/04/08 12:24:08 by llelias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static	void	evaluate_str(char buff[65], char *str, t_flags flags, int len)
{
	int div;
	int mod;
	int n;

	n = flags.width > len ? len : flags.width;
	div = flags.precision ? n / 64 : len / 64;
	mod = flags.precision ? n % 64 : len % 64;
	while (div-- && !(buff[64] = 0))
	{
		str += ft_strwcpy(buff, str, 64);
		ft_putstr(buff);
	}
	if (flags.precision && !(buff[mod] = 0))
		ft_strwcpy(buff, str, mod);
	else
	{
		ft_strwcpy(buff, str, mod);
		buff[mod] = 0;
	}
}

static	void	prints_alpha(char b[65], t_flags op)
{
	int		len;
	char	*pad;

	len = ft_strlen(b);
	pad = op.zero ? g_zeros : g_spaces;
	if (op.precision)
	{
		len = len >= op.width ? op.width : len;
		write(1, b, len);
	}
	else
	{
		if (!op.neg)
			putpad(pad, op.width - len);
		write(1, b, len);
		if (op.neg)
			putpad(pad, op.width - len);
	}
}

void			alpha_ph(char buff[65], va_list arg, t_flags flags)
{
	char	*str;
	int		len;

	if (flags.plhld == 's')
	{
		str = va_arg(arg, char*);
		len = ft_strlen(str);
		evaluate_str(buff, str, flags, len);
	}
	else
	{
		buff[0] = (char)va_arg(arg, int);
		buff[1] = 0;
	}
	prints_alpha(buff, flags);
}
