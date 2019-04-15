/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DONE_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelias <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:03:34 by llelias           #+#    #+#             */
/*   Updated: 2019/04/08 12:23:13 by llelias          ###   ########.fr       */
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

static	void	fixflags(t_flags *op)
{
	if (op->neg)
		op->zero = 0;
	if (op->precision)
		op->neg = 0;
	if (op->add)
		op->space = 0;
	if (op->alt && !(op->plhld == 'x' || op->plhld == 'X' || op->plhld == 'o'))
		op->alt = 0;
}

static	char	*setflags(char *f, t_flags *op)
{
	if (*f == '.' && f++)
		op->precision += 1;
	else if (is_num(*f) && *f != '0' && !op->width)
	{
		op->width = ft_atoi(f);
		while (is_num(*f))
			f++;
	}
	else if (*f == 'L' && f++)
		op->lfloat += 1;
	else if (*f == '0' && f++)
		op->zero += 1;
	else if (*f == '-' && f++)
		op->neg += 1;
	else if (*f == '+' && f++)
		op->add += 1;
	else if (*f == ' ' && f++)
		op->space += 1;
	else if (*f == 'l' && f++)
		op->l += 1;
	else if (*f == 'h' && f++)
		op->h += 1;
	else if (*f == '#' && f++)
		op->alt += 1;
	return (f);
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
	fixflags(&op);
	if (!*f)
		invalid(*f, 1);
	else if (*f == 'c' || *f == 's')
		alpha_ph(b, arg, &op);
	else if (*f == 'f')
		float_ph(b, arg, &op);
	else
		num_ph(b, arg, &op);
	return (++f);
}
