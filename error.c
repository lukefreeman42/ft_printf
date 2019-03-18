#include "ft_printf.h"

void    invalid_ph(char c)
{
        write(2, "\nERROR:ft_printf does not support this convertion", 49);
    exit(-1);
}