#include "ft_printf.h"

static int     end_ph(char c)
{
    char ph_tbl[11] = {'c', 's', 'p', 'd', 'i', 'o', 'u', 'x', 'X', '%', 0};
    int i;

    i = 0;
    while (ph_tbl[i])
        if (c == ph_tbl[i++])
            return (1);
    return (0);
}

static  void    zero_flags(t_flags *flags)
{
    flags->hh = 0;
    flags->h = 0;
    flags->ll = 0;
    flags->l = 0;
    flags->L = 0;
    flags->space = 0;
    flags->zero = 0;
    flags->neg = 0;
    flags->add = 0;
    flags->width = 0;
    flags->precision = 0;
    flags->X = 0;
}

static  char    *set_flags(char *f, t_flags *flags)
{
    if (*f == '.' && f++) //Precision
        flags->precision += 1;
    else if (is_num(*f) && *f != '0') //Width
    {
        if (!flags->width)
            flags->width = ft_atoi(f);
        else
            invalid_ph(*f);
        while (is_num(*f))
            f++;
    }
    else if (*f == '0' && f++)
        flags->zero += 1;
    else if (*f == '-' && f++)
        flags->neg += 1;
    else if (*f == '+' && f++)
        flags->add += 1;
    else if (*f == '%' && f++)
        write(1, "%", 1);
    return (f);
}
/*
Handle_PH must print the argument according to ph found,
and return the address of f after ph is parsed over.
*/
char    *handle_ph(char *f, char buff[65], va_list arg)
{
    t_flags flags;

    zero_flags(&flags);
    f++;
    if (*f == '%' && write(1, "%", 1))
        return (++f);
    while (!end_ph(*f) && *f)
        f = set_flags(f, &flags);
    if (*f == 'c')
        char_ph(buff, arg, flags);
    else if (*f == 's')
        str_ph(buff, arg, flags);
    else if (*f == 'p')
        p_ph(buff, arg, flags);
    /*
    else if (*f == 'd' || *f == 'i')
        1 == 1;
    else if (*f == 'o')
        1 == 1;
    else if (*f == 'u')
        1 == 1;
    else if (*f == ('x'))
        1 == 1;
    else if (*f == 'X')
        1 == 1;
    else if (*f == 'f')
        1 == 1;
    */
    else
        invalid_ph(*f);
    return (++f);
}