/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelias <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 16:24:11 by llelias           #+#    #+#             */
/*   Updated: 2019/04/02 18:49:32 by llelias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		putbuff(char b[65], int i)
{
	b[i] = 0;
	write(1, b, ft_strlen(b));
	return (0);
}

int				ft_printf(char *f, ...)
{
	char	b[65];
	va_list	arg;
	int		i;

	va_start(arg, f);
	i = 0;
	while (*f)
	{
		if (*f == '%')
		{
			i = putbuff(b, i);
			f = ph_handler(f, b, arg);
		}
		else
		{
			if (i == 63)
				i = putbuff(b, 64);
			b[i++] = *f++;
		}
	}
	putbuff(b, i);
	return (0);
}
