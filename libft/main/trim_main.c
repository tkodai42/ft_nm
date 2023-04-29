#include "libft.h"

void	exec(const char *str, const char *hint)
{
	char	*ret;

	ret = ft_strtrim(str, hint);
	printf("str [%s], hint [%s], trim [%s]\n", str, hint, ret);
}

int		main()
{
	exec("123abc123", "123");
	exec("123123", "123");
	exec("123abc123", "");
	exec("", "123");
	exec("", "");
	exec("123a", "123");
	exec("a123", "123");
}
