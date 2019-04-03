#include "ft_printf.h"

static char     convertion(int dig, t_flags flags) //turns digits > 10 into corresponding alphanumeric value
{
    if (dig < 10)
        return (dig + 48);
    else
    {
        if (flags.PH == 'X') //if X converstion, return them as capital letters
            return (dig + 55);
        else
            return (dig + 87);
    }
}

static long long trim_num(va_list arg, t_flags flags)
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

void    evaluate_num(char buff[65], long long num, t_flags flags, int base) //turns number into a string and puts it inside of buffer.
{
    int i;
    int flag;

    i = 0;
    flag = 0;
    if (num == 0)
        write(1, "0", 1); // maybe change to buff[0] = '0'
    else if (num < 0 && (num *= -1)) //if its a negative make positive, set a flag
        flag = 1;
    while (num) //while we parse through the number
    {
        buff[i++] = convertion(num % base, flags); //put the digit into the buffer
        num /= base;
    }
    if (flag) //if it was negative
        buff[i++] = '-'; //put the negative sign in the buffer
    buff[i] = 0; //null terminate the buffer
    ft_strrev(buff); //reverse the buffer so it can be read left to right.
}

void    num_ph(char buff[65], va_list arg, t_flags flags)
{
    long long num;
    int len;
    num = trim_num(arg, flags);
    if (flags.PH == 'd' || flags.PH == 'u')
        evaluate_num(buff, num, flags, 10);
    else if (flags.PH == 'o')
        evaluate_num(buff, num, flags, 8);
    else
        evaluate_num(buff, num, flags, 16);
    len = ft_strlen(buff);
    if (flags.PH == 'p')
        prints_addr(buff, flags);
    else
        prints_num(buff, flags);
}