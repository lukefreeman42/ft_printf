#include "ft_printf.h"

static char     convertion(int dig, t_flags flags)
{
    if (dig < 10)
        return (dig + 48);
    else
    {
        if (flags.PH == 'X')
            return (dig + 55);
        else
            return (dig + 87);
    }
}

void    num_handle(char buff[65], long long num, t_flags flags, int base)
{
    int i;
    int flag;

    i = 0;
    flag = 0;
    if (num == 0)
        write(1, "0", 1);
    else if (num < 0 && (num *= -1))
        flag = 1;
    while (num)
    {
        buff[i++] = convertion(num % base, flags);
        num /= base;
    }
    if (flag)
        buff[i++] = '-';
    buff[i] = 0;
    ft_strrev(buff);
}
/*
** Trims the number to the size specified in flags.
*/
static long long trim(va_list arg, t_flags flags)
{
    char hh;
    short h;
    int d;
    unsigned int u;
    long l;
    long long ll;
    if (flags.h == 2 && (hh = (char)va_arg(arg, int)))
        return ((long long)hh);
    else if (flags.h && (h = (short)va_arg(arg, int)))
        return ((long long)h);
    else if ((flags.l == 2 || flags.PH == 'p') && (ll = va_arg(arg, long long)))
        return ((long long)ll);
    else if (flags.l && (l = va_arg(arg, long)))
        return ((long long)l);
    else if (flags.PH != 'd' && (u = va_arg(arg, unsigned int)))
        return ((long long)u);
    d = va_arg(arg, int);
    return ((long long)d);
}

void    num_ph(char buff[65], va_list arg, t_flags flags)
{
    long long num;
    int len;
    num = trim(arg, flags);
    if (flags.PH == 'd' || flags.PH == 'u')
        num_handle(buff, num, flags, 10);
    else if (flags.PH == 'o')
        num_handle(buff, num, flags, 8);
    else
        num_handle(buff, num, flags, 16);
    len = ft_strlen(buff);
    if (flags.PH == 'p')
        prints(buff, flags, len, 2);
    else
        prints(buff, flags, len, 1);
}