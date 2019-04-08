/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ph.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelias <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:56:45 by llelias           #+#    #+#             */
/*   Updated: 2019/04/05 17:02:01 by llelias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	putpad(char pad[16], int a)
{
	int	div;
	int	mod;

	div = a / 16;
	mod = a % 16;
	while (div--)
		write(1, pad, 16);
	write(1, pad, mod);
}

static	char	*make_x(char b[65], t_flags *op, int *len)
{
	char *x;

	if (b[0] == '-')
		x = "-";
	else if (op->add)
		x = "+";
	else if (op->space)
		x = " ";
	else if (op->alt)
	{
		if (op->plhld == 'o')
			x = "0";
		else if (op->plhld == 'x')
			x = "0x";
		else if (op->plhld == 'X')
			x = "0X";
	}
	else
		x = "NULL";
	if (((op->add || op->space) && b[0] != '-' && op->plhld != 'f' && (op->width -= 1))
		|| (b[0] == '-' && op->precision && (*len -= 1))
		|| (op->plhld == 'o' && !op->precision && (op->width -= 1))
		|| (op->alt && op->plhld != 'o'
			&& *x != '-' && !op->precision && (op->width -= 2)))
		;
	return (x);
}

void			prints_alpha(char b[65], t_flags op)
{
	int		len;
	char	*pad;

	len = ft_strlen(b);
	pad = op.zero ? g_zeros : g_spaces;
	if (op.precision)
	{
		len = len >= op.width ? op.width : len;
		write(1, b, len);
	}
	else
	{
		if (!op.neg)
			putpad(pad, op.width - len);
		write(1, b, len);
		if (op.neg)
			putpad(pad, op.width - len);
	}
}

void			prints_num(char b[65], t_flags op)
{
	char	*x;
	int		len;
	char	*pad;

	len = ft_strlen(b);
	pad = (op.precision || op.zero) ? g_zeros : g_spaces;
	x = make_x(b, &op, &len);
	if (b[0] == '-')
		b++;
	if (pad == g_zeros && (op.add || op.space || *x == '-' || *x == '0'))
		write(1, x, ft_strlen(x));
	if (!op.neg)
		putpad(pad, op.width - len);
	if (pad == g_spaces && (op.add || op.space || *x == '-' || *x == '0'))
		write(1, x, ft_strlen(x));
	write(1, b, len);
	if (op.neg)
		putpad(pad, op.width - len);
}


static	void	round_float(char b[65], int i)
{
	int x;

	x = b[i + 1] == '.' ? 2 : 1;
	if (b[i + x] >= '5' && b[i] != '.')
		b[i] += 1;
}

void			prints_float(char b[65], t_flags op)
{
	int		int_len;
	int		frac_len;
	char	*x;
	char	*pad;

	int_len = 0;
	frac_len = 0;
	while (b[frac_len++] != '.')
		int_len++;
	frac_len = 7;
	pad = (op.precision || op.zero) ? g_zeros : g_spaces;
	x = make_x(b, &op, &frac_len);
	if (b[0] == '-')
			b++;
	if (pad == g_zeros && (op.add || op.space || *x == '-' || *x == '0'))
			write(1, x, ft_strlen(x));
	if (!op.neg && !op.precision)
		putpad(pad, op.width - int_len - frac_len);
	if (pad == g_spaces && (op.add || op.space || *x == '-' || *x == '0'))
		write(1, x, ft_strlen(x));
	if (op.precision)
	{
		round_float(b, int_len + op.width);
		if (op.width)
			write(1, b, op.width + int_len + 1);
		else
			write(1, b, int_len);
	}
	else
	{
		round_float(b, int_len + frac_len - 1);
		write(1, b, int_len + frac_len);
		if (op.neg)
			putpad(pad, op.width - int_len - frac_len);
	}
}