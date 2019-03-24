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
	while (ph_tbl[i])
		if (c == ph_tbl[i++] && (flags->PH = ph_tbl[i - 1]))
			return (1);
	return (0);
}

static	void	zeroflags(t_flags *flags)
{
	ft_memset(flags, 0, sizeof(*flags));
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

char		*ph_handler(char *f, char buff[65], va_list arg)
{
	t_flags flags;

	zeroflags(&flags);
	f++;
	if (*f == '%' && write(1, "%", 1))
		return (++f);
	while (!is_ph(*f, &flags) && *f)
		f = setflags(f, &flags);
	if (!*f)
		invalid(*f, 1);
	else if (*f == 'c' || *f == 's')
		alpha_ph(buff, arg, flags);
	else if (*f == 'f')
		float_ph(buff, arg, flags);
	else
		num_ph(buff, arg, flags);
	return (++f);
}
