#include "ft_printf.h"

static void putpad(char pad[16], int a)
{
    int div;
    int mod;

    div = a / 16;
    mod = a % 16;
    while (div--)
        write(1, pad, 16);
    write(1, pad, mod);
}

void    char_ph(char buff[65], va_list arg, t_flags flags)
{
    char c;

    c = (char)va_arg(arg, int);
    write(1, &c, 1);
}

void    str_ph(char buff[65], va_list arg, t_flags flags)
{
    char    *str;
    int     n;
    int     len;
    char    *pad;

    n = flags.width;
    pad = flags.zero ? zeros : spaces;
    str = va_arg(arg, char*);
    if (flags.precision && !(buff[n] = 0))
        ft_strwcpy(buff, str, n);
    else
    {
        len = ft_strlen(str);
        ft_strwcpy(buff, str, len);
        buff[len] = 0;
        if (!flags.neg)
            putpad(pad, n - len);
    }
    ft_putstr(buff);
        if (flags.neg && !flags.precision)
            putpad(spaces, n - len);
}