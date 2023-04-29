#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	bytes = count * size;
	char	*dest = malloc(bytes);
	size_t	i = 0;

	while (i < bytes)
	{
		dest[i] = 0;
		i++;
	}
	return dest;
}
