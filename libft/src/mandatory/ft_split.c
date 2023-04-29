#include "libft.h"

char **ft_split(char *str, char *charset);

int		count_word(char *str, char *charset)
{
	int		count = 0;

	while (*str)
	{
		while (*str && ft_strchr(charset, *str))	
			str++;
		if (*str)
			count++;	
		while (*str && ft_strchr(charset, *str) == NULL)	
			str++;
	}
	return count;
}

char	*get_word(char **str, char *charset)
{
	char *head = *str;
	char *tail;
	char *dest;

	while (*head && ft_strchr(charset, *head))
		head++;
	tail = head;
	while (*tail && ft_strchr(charset, *tail) == NULL)
		tail++;
	dest = ft_calloc(tail - head + 1, sizeof(char));
	if (dest == NULL)
		return NULL;
	ft_memcpy(dest, head, tail - head);
	return dest;
}

char **free_table(char **table, int size)
{
	int i = 0;

	while (i < size)
	{
		free(table[i]);
		i++;
	}
	free(table);
	ft_malloc_error();
	return NULL;
}

char **ft_split(char *str, char *charset)
{
	int		tab_count = 0;
	char	**table;
	int		i = 0;

	if (!str || !charset)
		return NULL;
	tab_count = count_word(str, charset);
	table = malloc(sizeof(char *) * (tab_count + 1));
	if (table == NULL)
	{
		ft_malloc_error();
		return NULL;
	}

	table[tab_count] = NULL;
	while (i < tab_count)
	{
		table[i] = get_word(&str, charset);
		if (table[i] == NULL)
			return (free_table(table, i));
		i++;
	}
	return table;
}
/*
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
*/
