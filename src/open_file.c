#include "../includes/ft_nm.h"
#include "../includes/elf.h"

void	put_file_error(char *file_name)
{
	ft_putstr(ES_WORD_RED);
	ft_putstr(ES_BOLD);
	ft_putstr("error: ");
	ft_putstr(ES_RESET);
	ft_putstr(file_name);
	ft_putstr(": ");
	ft_putstr(strerror(errno));
	ft_putstr(".\n");
}

int		get_file_size(int fd)
{
	struct stat sb;

	fstat(fd, &sb);
	//error???
	return sb.st_size;
}

void	set_mmap(t_ft_nm *ft_nm, int fd)
{
	ft_nm->file_size = get_file_size(fd);
	ft_nm->head = mmap(NULL, ft_nm->file_size, PROT_READ, MAP_SHARED, fd, 0);
}

void	execute(t_ft_nm *ft_nm)
{
	t_list_node	*node;
	int			fd;
	char		*current_file_ptr;

	node = ft_nm->file_list;
	while (node)
	{
		current_file_ptr = (char*)node->content;
		ft_nm->file_name = current_file_ptr;
		//open_file
		fd = open(current_file_ptr, O_RDWR);
		if (fd == -1)
		{
			put_file_error(current_file_ptr);
		}
		else
		{
			set_mmap(ft_nm, fd);;
			nm_solve(ft_nm);
		}
		node = node->next;
		close(fd);
	}
}
