#include "ft.h"

int	ft_strlen(char *str)
{
	const char *c = str;

	while (*c)
		c++;
	return c - str;
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}
