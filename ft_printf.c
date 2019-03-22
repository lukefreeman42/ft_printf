#include "ft_printf.h"

static	int		putbuff(char buff[65], int i)
{
	buff[i] = 0;
	write(1 ,buff, ft_strlen(buff));
	return (0);
}

static	void	ft_prints(char *f, char buff[65], va_list arg)
{
	int i;

	i = 0;
	while (*f)
	{
		if (*f == '%')
		{
			i = putbuff(buff, i);
			f = handle_ph(f, buff, arg);
		}
		else
        {
            if (i == 63)
                i = putbuff(buff, 64);
            buff[i++] = *f++;
        }
    }
    putbuff(buff, i);
}

int     ft_printf(char *f, ...)
{
    char buff[65];

    va_list arg;
    va_start(arg, f);
    ft_prints(f, buff, arg);
    return (0);
}
