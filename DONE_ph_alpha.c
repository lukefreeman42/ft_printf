/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_alpha.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelias <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:14:24 by llelias           #+#    #+#             */
/*   Updated: 2019/04/02 18:14:27 by llelias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
