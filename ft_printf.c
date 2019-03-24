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

int				ft_printf(char *f, ...)
{
	char	buff[65];
	va_list	arg;
	int i;

	va_start(arg, f);
	i = 0;
	while (*f)
	{
		if (*f == '%')
		{
			i = putbuff(buff, i);
			f = ph_handler(f, buff, arg);
		}
		else
		{
			if (i == 63)
				i = putbuff(buff, 64);
			buff[i++] = *f++;
		}
	}
	putbuff(buff, i);
	return (0);
}