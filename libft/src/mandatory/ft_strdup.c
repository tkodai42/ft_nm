#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dest;
	char	*save;

	if (str == NULL)
		return NULL;
	dest = malloc(ft_strlen(str) + 1);
	if (dest == NULL)
		return NULL;
	save = dest;
	while (*str)
		*dest++ = *str++;
	*dest = '\0';
	return save;
}
