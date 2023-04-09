#include "ft_nm.h"

void	put_file_error(const char *file_path)
{
	ft_putstr_fd(ES_WORD_RED, 2);	
	ft_putstr_fd(ES_BOLD, 2);	
	ft_putstr_fd("error: ", 2);	
	ft_putstr_fd(ES_RESET, 2);	
	ft_putstr_fd(file_path, 2);	
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(".\n", 2);
}

void	execute_nm(t_ft_nm *ft_nm)
{
	t_list_node *node = ft_nm->file_list;
	char		*file_path;
	int			fd;

	while (node)
	{
		file_path = (char*)node->content;
		fd = open(file_path, O_RDONLY);
		if (fd == -1)
		{
			put_file_error(file_path);
		}


		node = node->next;
	}

}
