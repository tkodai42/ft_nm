#include "libft.h"

void	checker(int num)
{
	char	*ret = NULL;

	ret = ft_itoa(num);
	printf("num: %d -> str: %s\n", num, ret);
}

int		main()
{
	checker(123);
	checker(0);
	checker(-123456);
}
