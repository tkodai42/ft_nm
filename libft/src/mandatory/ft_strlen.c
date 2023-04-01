#include "libft.h"

int		ft_strlen(const char *str)
{
	const char *c = str;

	while (*c)
		c++;
	return c - str;
}
