#include "ft_printf.h"

static char zeros[16] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
static char spaces[16] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};

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

/*
** num; 
**      0 = c/s
**      1 = d/i/o/u/x/X
**      2 = p
*/
void    prints(char buff[65], t_flags flags, int len, int num)
{
    int n;
    char *pad;

    n = flags.width;
    pad = flags.zero ? zeros : spaces;
    if (num == 1 && flags.precision)
        pad = zeros;
    if  (!flags.neg && !flags.precision && !flags.zero && n > len)
            putpad(pad, n - len);
    if (num == 2 && (n -= 2))
        write(1, "0x", 2);
    if (flags.precision && num == 2)
        putpad(zeros, n - len + 2);
    if (!flags.neg && !flags.precision && n > len)
    {
        if (num == 1)
            if (buff[0] == '-')
                write(1, buff++, 1);
        putpad(pad, n - len);
    }
    write(1, buff, ft_strlen(buff)); 
    if (flags.neg && !flags.precision && n > len)
        putpad(spaces, n - len);
}