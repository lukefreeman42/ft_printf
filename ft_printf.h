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

#define MAX_ULONG 1844674407370955161

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

static	char	ph_tbl[11] = {'c', 's', 'p', 'd', 'i', 'o', 'u', 'x', 'X', 'f', 0};
static	char	zeros[16] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
static	char	spaces[16] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};

int		ft_printf(char *f, ...);
char	*ph_handler(char *f, char buff[65], va_list arg);
void	alpha_ph(char buff[65], va_list arg, t_flags flags);
void	num_ph(char buff[65], va_list arg, t_flags flags);
void    float_ph(char buff[64], va_list arg, t_flags flags);
void    evaluate_num(char buff[65], long long num, t_flags flags, int base);
void	prints_ph(char buff[65], t_flags flags, int num);
void	invalid(char c, int i);

void	prints_addr(char buff[65], t_flags flags);
void	prints_alpha(char buff[65], t_flags flags);
void	prints_num(char buff[65], t_flags flags);
void	prints_float(char buff[65], t_flags flags);