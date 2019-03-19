#include "ft_printf.h"

static char     convertion(int dig, t_flags flags)
{
    if (dig < 10)
        return (dig + 48);
    else
    {
        if (flags.X)
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
    else
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

void    p_ph(char buff[65], va_list arg, t_flags flags)
{
    long long num;
    int len;
    int n;
    char *pad;

    n = flags.width - 2;
    num = va_arg(arg, long long);
    num_handle(buff, num, flags, 16);
    len = ft_strlen(buff);
    pad = flags.zero ? zeros : spaces;
    if (!flags.precision && !flags.neg && !flags.zero && n > len)
        putpad(pad, n - len);
    write(1, "0x", 2);
    if (!flags.precision && !flags.neg && flags.zero && n > len)
        putpad(pad, n - len);
    if (flags.precision)
        putpad(zeros, n - len + 2);
    write(1, buff, len);
    if (!flags.precision && flags.neg && n > len)
        putpad(spaces, n - len);
}