#include <stdarg.h>
#include <libft.h>

typedef struct  s_flags
{
    int     h;
    int     l;
    int     L;
    int     space;
    int     zero;
    int     neg;
    int     add;
    int     precision;
    int     width;
    int     PH;
}               t_flags;

static char zeros[16] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
static char spaces[16] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};

int     ft_printf(char *f, ...);
char    *handle_ph(char *f, char buff[65], va_list arg);
void    invalid_ph(char c);

void    prints(char buff[65], t_flags flags, int len, int num);
void    str_ph(char buff[65], va_list arg, t_flags flags);
void    d_ph(char buff[65], va_list arg, t_flags flags);
void    char_ph(char buff[65], va_list arg, t_flags flags);
void    p_ph(char buff[65], va_list arg, t_flags flags);
void    o_ph(char buff[65], va_list arg, t_flags flags);
void    x_ph(char buff[65], va_list arg, t_flags flags);
void    X_ph(char buff[65], va_list arg, t_flags flags);
void    u_ph(char buff[65], va_list arg, t_flags flags);
void    num_ph(char buff[65], va_list arg, t_flags flags);