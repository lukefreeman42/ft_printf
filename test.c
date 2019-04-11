#include "ft_printf.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	long long b = 234;
	char *s = "TESTER675";
	double d = -123.4322344532;

	ft_printf(argv[1],b, &b, s,d);
	printf("\n");
	printf(argv[1],b,&b, s, d);
}
