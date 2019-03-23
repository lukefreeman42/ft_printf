#include "ft_printf.h"

static  double  trim_float(va_list arg, t_flags flags)
{
    double  d;
    float   f;

    if (flags.L && (d = va_arg(arg, double)))
        return (d);
    f = va_arg(arg, double);
    return ((double)f);
}

static void     float_handle(char buff[65], double num, t_flags flags)
{
    long long   floor;
    long long   tot;
    double      remainder;
    int         i;

    i = 0;
    floor = (long long) num;
    num_handle(buff, floor, flags, 10);
    remainder = num - (double) floor;
    while (buff[i])
        i++;
    buff[i++] = '.';
    tot = 0;
    while (remainder && tot < MAX_ULONG)
    {
        num = remainder * 10;
        floor = (long long)num;
        tot = tot * 10 + floor;
        remainder = num - (double)floor;
    }
    num_handle(buff + i, tot, flags, 10);
}
void    float_ph(char buff[64], va_list arg, t_flags flags)
{
    double  f;

    f = trim_float(arg, flags);
    float_handle(buff, f, flags);
    prints(buff, flags, 8, 3);
}