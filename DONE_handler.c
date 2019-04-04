/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelias <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 16:44:35 by llelias           #+#    #+#             */
/*   Updated: 2019/04/02 18:48:50 by llelias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		is_ph(char c, t_flags *op)
{
	int i;

	i = 0;
	while (g_ph_tbl[i])
		if (c == g_ph_tbl[i++] && (op->plhld = g_ph_tbl[i - 1]))
			return (1);
	return (0);
}

static	void	zeroflags(t_flags *op)
{
	ft_memset(op, 0, sizeof(*op));
}

static	char	*setflags(char *f, t_flags *op)
{
	if (*f == '.')
		op->precision += 1;
	else if (is_num(*f) && *f != '0')
	{
		if (!op->width)
			op->width = ft_atoi(f);
		else
			invalid(*f, 2);
		while (is_num(*f))
			f++;
		return (f);
	}
	else if (*f == '0')
		op->zero += 1;
	else if (*f == '-')
		op->neg += 1;
	else if (*f == '+')
		op->add += 1;
	else if (*f == '%')
		write(1, "%", 1);
	else if (*f == 'l')
		op->l += 1;
	else if (*f == 'h')
		op->h += 1;
	return (++f);
}

char			*ph_handler(char *f, char b[65], va_list arg)
{
	t_flags op;

	zeroflags(&op);
	f++;
	if (*f == '%' && write(1, "%", 1))
		return (++f);
	while (!is_ph(*f, &op) && *f)
		f = setflags(f, &op);
	if (!*f)
		invalid(*f, 1);
	else if (*f == 'c' || *f == 's')
		alpha_ph(b, arg, op);
	else if (*f == 'f')
		float_ph(b, arg, op);
	else
		num_ph(b, arg, op);
	return (++f);
}