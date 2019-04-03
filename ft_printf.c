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
	char	buff[65]; // Store everything we parse that is not a place holder
	va_list	arg;
	int		i;

	va_start(arg, f); //Grabs arguments
	i = 0;
	while (*f) //Parse format string
	{
		if (*f == '%') //If placeholder is found
		{
			i = putbuff(buff, i); //Print buffer, reset buffer
			f = ph_handler(f, buff, arg); //Evaluate and print evaluated placeholder, increment over placeholder
		}
		else
		{
			if (i == 63) //If buffer is full
				i = putbuff(buff, 64);
			buff[i++] = *f++; //Increment buffer and format string
		}
	}
	putbuff(buff, i);
	return (0);
}
