#include "ft_printf.h"

void putpad(char pad[16], int a)
{
    int div;
    int mod;

    div = a / 16;
    mod = a % 16;
    while (div--)
        write(1, pad, 16);
    write(1, pad, mod);
}

static void putbuff(char buff[65], char *str, t_flags flags, int len)
{
    int div;
    int mod;
    int n;

    n = flags.width > len ? len : flags.width;
    div = flags.precision ? n / 64 : len / 64;
    mod = flags.precision ? n % 64 : len % 64;
    while (div-- && !(buff[64] = 0))
    {
        str += ft_strwcpy(buff, str, 64);
        ft_putstr(buff);
    }
    if (flags.precision && !(buff[mod] = 0))
        ft_strwcpy(buff, str, mod);
    else
    {
        ft_strwcpy(buff, str, mod);
        buff[mod] = 0;
    }
    ft_putstr(buff);
}

void    str_ph(char buff[65], va_list arg, t_flags flags)
{
    char    *str;
    int     n;
    int     len;
    char    *pad;

    str = va_arg(arg, char*);
    n = flags.width;
    len = ft_strlen(str);
    pad = flags.zero ? zeros : spaces;
    if (!flags.neg && !flags.precision && n > len)
            putpad(pad, n - len);
    putbuff(buff, str, flags, len);
    if (flags.neg && !flags.precision && n > len)
        putpad(spaces, n - len);
}

void    char_ph(char buff[65], va_list arg, t_flags flags)
{
    char c;
    int n;
    char *pad;

    n = flags.width;
    c = (char)va_arg(arg, int);
    pad = flags.zero ? zeros : spaces;
    if (!flags.neg && !flags.precision && n > 1)
        putpad(pad, n - 1);
    write(1, &c, 1);
    if (flags.neg && !flags.precision && n > 1)
        putpad(spaces, n - 1);
}