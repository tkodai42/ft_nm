#include "libft.h"

char	*ft_strtrim(const char *str, const char *set)
{
	const char	*head;
	const char	*tail;
	char		*save;
	char		*dest;

	if (set == NULL)
		return ft_strdup(str);
	head = str;
	while (*head && ft_strchr(set, *head))
		head++;
	tail = str + ft_strlen(str);
	while (head < tail && ft_strchr(set, *(tail - 1)))
		tail--;

	save = malloc(tail - head + 1);
	dest = save;
	if (save == NULL)
		return NULL;
	while (head < tail)	
		*dest++ = *head++;
	*dest = '\0';
	return save;
}

/*
void	exec(char *str, char *set)
{
	printf("str:[%s] set:[%s] [%s]\n", str, set, ft_strtrim(str, set));
}

int		main()
{
	exec("123", "13");
	exec("0000", "0");
	exec("0012300", "0");
	exec("", "0");
}
*/
