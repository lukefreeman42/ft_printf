/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelias <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 16:24:11 by llelias           #+#    #+#             */
/*   Updated: 2019/03/22 16:25:14 by llelias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		putbuff(char buff[65], int i)
{
	buff[i] = 0;
	write(1, buff, ft_strlen(buff));
	return (0);
}

static	void	ft_prints(char *f, va_list arg)
{
	char	buff[65];
	int		i;

	i = 0;
	while (*f)
	{
		if (*f == '%')
		{
			i = putbuff(buff, i);
			f = handle_ph(f, buff, arg);
		}
		else
		{
			if (i == 63)
				i = putbuff(buff, 64);
			buff[i++] = *f++;
		}
	}
	putbuff(buff, i);
}

int				ft_printf(char *f, ...)
{
	va_list	arg;

	va_start(arg, f);
	ft_prints(f, arg);
	return (0);
}
