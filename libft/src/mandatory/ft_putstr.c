#include "libft.h"

int		ft_putstr(const char *str)
{
	return write(1, str, ft_strlen(str));
}
