#include <stdarg.h>
#include <libft.h>

typedef struct  s_flags
{
    int     hh;
    int     h;
    int     ll;
    int     l;
    int     L;
    int     space;
    int     zero;
    int     neg;
    int     add;
    int     precision;
    int     width;
}               t_flags;

static char zeros[16] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
static char spaces[16] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};

int     ft_printf(char *f, ...);
char    *handle_ph(char *f, char buff[65], va_list arg);
void    invalid_ph(char c);
void putpad(char pad[16], int a);
void    str_ph(char buff[65], va_list arg, t_flags flags);
void    char_ph(char buff[65], va_list arg, t_flags flags);
void    p_ph(char buff[65], va_list arg, t_flags flags);