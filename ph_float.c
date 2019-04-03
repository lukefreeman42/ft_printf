#include "ft_printf.h"

static  double      trim_float(va_list arg, t_flags flags) //grabs and returns the argument given for this Placeholder
{
    double  d;
    float   f;

    if (flags.L && (d = va_arg(arg, double))) //if flag 'L', arg is a double
        return (d);
    f = va_arg(arg, double); //else its a float
    return ((double)f); //return the argument
}

static  long long   get_mantissa(double num, double i_half) //returns the fractional_part of the double
{
    long long   f_half;
    double      remain;
    
    f_half = 0;
    remain = num - (double) i_half; //remove the integer part
    while (remain && f_half <  (long long)MAX_ULONG) //while the fractional part fits within a long long
    {
        //shift the decimal point one place to the right until it reaches the end, or exceeds a long long
        num = remain * 10; 
        i_half = (long long)num;
        f_half = f_half * 10 + i_half;
        remain = num - (double)i_half;
    }
    return (f_half);
}

static  void        evaluate_float(char buff[65], double num, t_flags flags) //fills buffer with float to print out
{
    long long   integer_half;
    long long   fractional_half;
    int         i;

    i = 0;
    integer_half = (long long) num; //floor the float, giving only the interger half
    evaluate_num(buff, integer_half, flags, 10); //put the integer half into the buffer
    while (buff[i]) //parse the interger part
        i++;
    buff[i++] = '.'; //put down the decimal point
    fractional_half = get_mantissa(num, integer_half); //grab fractional part
    evaluate_num(buff + i, fractional_half, flags, 10); //add fractional part to the buffer
}

void                float_ph(char buff[64], va_list arg, t_flags flags)
{
    double  f;

    f = trim_float(arg, flags);
    evaluate_float(buff, f, flags);
    prints_float(buff, flags);
}