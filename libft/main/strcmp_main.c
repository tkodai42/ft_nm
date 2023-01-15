#include "libft.h"

void	checker(const char *s1, const char *s2)
{
	int		ret = ft_strcmp(s1, s2);

	printf("[%s] [%s]: %d\n", s1, s2, ret);
}

int		main()
{
	checker("123", "123");
	checker("", "");
	checker("1", "");
	checker("1234", "12345");
	checker("11345", "12345");
}
