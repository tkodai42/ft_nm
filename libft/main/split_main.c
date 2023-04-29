#include "libft.h"

void	exec(char *str, char *charset)
{
	printf("str: [%s] charset: [%s]\n", str, charset);

	char 	**ret = ft_split(str, charset);
	int		i = 0;

	while (ret)
	{
		printf(" [%d]%s\n", i, ret[i]);
		if (ret[i] == NULL)
			break ;
		i++;	
	}

}

int		main()
{
	exec("123a123b123", "abc");
	exec("abcabc", "abc");
	exec("aaa111bbb111ccc", "abc");
	exec("", "abc");
	exec("aaa", "");
}
