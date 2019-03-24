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

static long long get_mantissa(double num, double i_half)
{
    long long   f_half;
    double      remain;
    
    f_half = 0;
    remain = num - (double) i_half;
    while (remain && f_half < MAX_ULONG)
    {
        num = remain * 10;
        i_half = (long long)num;
        f_half = f_half * 10 + i_half;
        remain = num - (double)i_half;
    }
    return (f_half);
}

static void     evaluate_float(char buff[65], double num, t_flags flags)
{
    long long   integer_half;
    long long   fractional_half;
    int         i;

    i = 0;
    integer_half = (long long) num;
    evaluate_num(buff, integer_half, flags, 10);
    while (buff[i])
        i++;
    buff[i++] = '.';
    fractional_half = get_mantissa(num, integer_half);
    evaluate_num(buff + i, fractional_half, flags, 10);
}

void    float_ph(char buff[64], va_list arg, t_flags flags)
{
    double  f;

    f = trim_float(arg, flags);
    evaluate_float(buff, f, flags);
    prints_ph(buff, flags, 8, 3);
}