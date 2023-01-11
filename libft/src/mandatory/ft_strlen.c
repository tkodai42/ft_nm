#include "libft.h"

int		ft_strlen(const char *str)
{
	int i = 0;

	while (*str)
	{
		i++;
		str++;
	}
	return i;
}
