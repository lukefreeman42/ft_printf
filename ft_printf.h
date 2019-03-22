/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelias <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 16:39:28 by llelias           #+#    #+#             */
/*   Updated: 2019/03/22 16:39:30 by llelias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <libft.h>

typedef	struct	s_flags
{
	int	h;
	int	l;
	int	L;
	int	space;
	int	zero;
	int	neg;
	int	add;
	int	precision;
	int	width;
	int	PH;
}				t_flags;

static char ph_tbl[10] = {'c', 's', 'p', 'd', 'i', 'o', 'u', 'x', 'X', 0};

int		ft_printf(char *f, ...);
char	*handle_ph(char *f, char buff[65], va_list arg);
void	invalid_ph(char c);
void	alpha_ph(char buff[65], va_list arg, t_flags flags);
void	num_ph(char buff[65], va_list arg, t_flags flags);
void	prints(char buff[65], t_flags flags, int len, int num);
