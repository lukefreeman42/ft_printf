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

static	int		end_ph(char c, t_flags *flags)
{
	int i;

	i = 0;
	while (ph_tbl[i])
		if (c == ph_tbl[i++] && (flags->PH = ph_tbl[i - 1]))
			return (1);
	return (0);
}

static	void	zero_flags(t_flags *flags)
{
	flags->h = 0;
	flags->l = 0;
	flags->L = 0;
	flags->space = 0;
	flags->zero = 0;
	flags->neg = 0;
	flags->add = 0;
	flags->width = 0;
	flags->precision = 0;
	flags->PH = 0;
}

static	char	*set_flags(char *f, t_flags *flags)
{
	if (*f == '.')
		flags->precision += 1;
	else if (is_num(*f) && *f != '0')
	{
		if (!flags->width)
			flags->width = ft_atoi(f);
		else
			invalid_ph(*f);
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

char		*handle_ph(char *f, char buff[65], va_list arg)
{
	t_flags flags;

	zero_flags(&flags);
	f++;
	if (*f == '%' && write(1, "%", 1))
		return (++f);
	while (!end_ph(*f, &flags) && *f)
		f = set_flags(f, &flags);
	if (!*f)
		invalid_ph(*f);
	else if (*f == 'f')
		;
	else if (*f == 'c' || *f == 's')
		alpha_ph(buff, arg, flags);
	else
		num_ph(buff, arg, flags);
	return (++f);
}
