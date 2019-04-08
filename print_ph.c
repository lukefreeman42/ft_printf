/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ph.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelias <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:14:01 by llelias           #+#    #+#             */
/*   Updated: 2019/04/08 12:19:21 by llelias          ###   ########.fr       */
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

static	char	*make_pfx(t_flags *op)
{
	char *x;

	if (op->negsign)
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
	if (!op->precision || (op->alt && op->plhld == 'o'))
	{
		if (op->add || op->space || op->negsign || op->plhld == 'o')
			op->width -= 1;
		else if (op->alt && op->plhld != 'o')
			op->width -= 2;
	}
	return (x);
}

static	void	prep_print(char b[65], t_flags *op)
{
	int x;
	int i;

	i = 0;
	while (b[i] != '.' && b[i++])
		op->len++;
	op->flen = 0;
	if (op->plhld == 'f')
	{
		op->flen = 7;
		if (op->precision)
			i = op->len + op->width;
		else
			i = op->len + op->flen - 1;
		if (b[i] == '.')
			i--;
		x = b[i + 1] == '.' ? 2 : 1;
		if (b[i + x] >= '5' && b[i] != '.')
			b[i] += 1;
	}
}

static void		print_prefix(t_flags *op)
{
	char *pfx;

	op->pad = (op->precision || op->zero) ? g_zeros : g_spaces;
	pfx = make_pfx(op);
	if (op->pad == g_zeros && (op->add || op->space || op->negsign || op->alt))
		write(1, pfx, ft_strlen(pfx));
	if ((!op->neg && !op->precision) || (!op->neg && op->plhld != 'f'))
		putpad(op->pad, op->width - op->len - op->flen);
	if (op->pad == g_spaces && (op->add || op->space || op->negsign || op->alt))
		write(1, pfx, ft_strlen(pfx));
}

void			prints_num(char b[65], t_flags op)
{
	prep_print(b, &op);
	print_prefix(&op);
	if (op.precision && op.plhld == 'f')
	{
		if (op.width)
		{
			if (op.width > 19 && (write(1, b, 19 + op.len + 1)))
				putpad(g_zeros, op.width - 19);
			else
				write(1, b, op.width + op.len + 1);
		}
		else
			write(1, b, op.len);
	}
	else
	{
		write(1, b, op.len + op.flen);
		if (op.neg)
			putpad(op.pad, op.width - op.len - op.flen);
	}
}
