/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelias <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 16:39:28 by llelias           #+#    #+#             */
/*   Updated: 2019/04/11 18:55:32 by llelias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "./../libft.h"
# define MAX_LONGLONG 9223372036854775807

typedef	struct	s_flags
{
	int		h;
	int		l;
	int		lfloat;
	int		space;
	int		zero;
	int		neg;
	int		add;
	int		precision;
	int		width;
	int		plhld;
	int		alt;
	int		negsign;
	int		len;
	int		flen;
	char	*pad;
}				t_flags;

typedef struct	s_trim
{
	char			hh;
	short			h;
	int				d;
	unsigned int	u;
	long			l;
	long long		ll;
}				t_trim;

int				ft_printf(char *f, ...);
char			*ph_handler(char *f, char b[65], va_list arg);
void			alpha_ph(char b[65], va_list arg, t_flags *flags);
void			num_ph(char b[65], va_list arg, t_flags *flags);
void			float_ph(char b[64], va_list arg, t_flags *flags);
void			prints_num(char b[65], t_flags flags);
void			eval_num(char b[65], long long num, t_flags *flags, int bse);
void			invalid(char c, int i);
static	char	g_ph_tbl[11] = {'c', 's', 'p', 'd', 'i',
	'o', 'u', 'x', 'X', 'f', 0};
static	char	g_zeros[16] = {'0', '0', '0', '0', '0', '0', '0', '0',
	'0', '0', '0', '0', '0', '0', '0', '0'};
static	char	g_spaces[16] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
#endif
