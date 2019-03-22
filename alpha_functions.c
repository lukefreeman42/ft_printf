#include "ft_printf.h"

static void str_handle(char buff[65], char *str, t_flags flags, int len)
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
}
void    alpha_ph(char buff[65], va_list arg, t_flags flags)
{
    char    *str;
    int     len;
    
    if (flags.PH == 's')
    {
        str = va_arg(arg, char*);
        len = ft_strlen(str);
        str_handle(buff, str, flags, len);
    }
    else
    {
        buff[0] = (char)va_arg(arg, int);
        buff[1] = 0;
        len = 1;
    }
    prints(buff, flags, len, 0);
}