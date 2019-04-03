/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelias <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 16:44:35 by llelias           #+#    #+#             */
/*   Updated: 2019/03/22 16:45:04 by llelias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		is_ph(char c, t_flags *flags)
{
	int i;

	i = 0;
	while (ph_tbl[i]) //check place_holder table for char c
		if (c == ph_tbl[i++] && (flags->PH = ph_tbl[i - 1])) //if char c is inside our table, set the PlaceHolder flag and return True
			return (1);
	return (0);
}

static	void	zeroflags(t_flags *flags)
{
	ft_memset(flags, 0, sizeof(*flags)); //sets the address block of flags all to 0
}

static	char	*setflags(char *f, t_flags *flags)
{
	if (*f == '.')
		flags->precision += 1;
	else if (is_num(*f) && *f != '0')
	{
		if (!flags->width)
			flags->width = ft_atoi(f);
		else
			invalid(*f, 2);
		while (is_num(*f))
			f++;
		return (f);
	}
	else if (*f == '0')
		flags->zero += 1;
	else if (*f == '-')
		flags->neg += 1;
	else if (*f == '+')
		flags->add += 1;
	else if (*f == '%')
		write(1, "%", 1);
	else if (*f == 'l')
		flags->l += 1;
	else if (*f == 'h')
		flags->h += 1;
	return (++f);
}

char			*ph_handler(char *f, char buff[65], va_list arg) //sets flags, and calls the correct function to handle the printing
{
	t_flags flags; //flags that define how we evaluate placeholder

	zeroflags(&flags); //reset flags
	f++;
	if (*f == '%' && write(1, "%", 1)) //if '%%' print '%'
		return (++f); //return
	while (!is_ph(*f, &flags) && *f) //while we are parsing through optional flags
		f = setflags(f, &flags);
	if (!*f) //if we didn't find a converstion flag, we don't support it
		invalid(*f, 1);
	else if (*f == 'c' || *f == 's') //if converstion flag is 'c' or 's'
		alpha_ph(buff, arg, flags); //evaluate and print 
	else if (*f == 'f') 
		float_ph(buff, arg, flags);
	else
		num_ph(buff, arg, flags);
	return (++f); //place the parser right after the placeholder
}
