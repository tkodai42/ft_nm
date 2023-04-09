#include "ft_nm.h"



int		get_file_size(int fd)
{
	struct stat		sb;

	if (fstat(fd, &sb) == -1)
		return -1;
	return sb.st_size;
}

int		set_mmap(t_ft_nm *ft_nm, int fd)
{
	ft_nm->file_size = get_file_size(fd);
	if (ft_nm->file_size == -1)
		return -1;
	ft_nm->file_head = mmap(NULL, ft_nm->file_size, PROT_READ, MAP_SHARED, fd, 0);	
	if ((int)ft_nm->file_head == -1)
		return -1;
	return 0;
}

void	execute_nm(t_ft_nm *ft_nm)
{
	t_list_node *node = ft_nm->file_list;
	char		*file_path;
	int			fd;

	while (node)
	{
		file_path = (char*)node->content;
		ft_nm->file_name = file_path;
		fd = open(file_path, O_RDONLY);
		if (fd == -1)
		{
			put_file_error(file_path);
		}
		else
		{
			if (set_mmap(ft_nm, fd) == -1)
			{
				put_file_error(file_path);
			}
			else
			{
				set_end_offset(ft_nm);
				nm_solve(ft_nm);			
				munmap(ft_nm->file_head, ft_nm->file_size);
				if (ft_nm->status != NM_STATUS_0)
					put_nm_error(ft_nm);
			}
		}
		node = node->next;
		close(fd);
	}
}
