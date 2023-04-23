#include "ft_nm.h"

int		get_file_size(int fd)
{
	struct stat		st;

	if (fstat(fd, &st) == -1)
		return -1;
	return st.st_size;
}

int		set_mmap(t_ft_nm *ft_nm, int fd)
{
	ft_nm->file_size = get_file_size(fd);
	if (ft_nm->file_size == 0)
		return -1;
	if (ft_nm->file_size == -1)
	{
		ft_nm->status_msg = strerror(errno);
		put_file_error(ft_nm, ft_nm->file_name);
		return -1;
	}
	ft_nm->file_head = mmap(NULL, ft_nm->file_size, PROT_READ, MAP_SHARED, fd, 0);	
	if ((long long)ft_nm->file_head == -1)
	{
		ft_nm->status_msg = strerror(errno);
		put_file_error(ft_nm, ft_nm->file_name);
		return -1;
	}
	return 0;
}

int		open_file(t_ft_nm *ft_nm)
{
	struct stat		st;
	int				fd;

	fd = open(ft_nm->file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_nm->status_msg = "No such file";
		return fd;
	}
	if (fstat(fd, &st) == -1)
	{
		ft_nm->status_msg = strerror(errno);
		return -1;
	}
	if ((st.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_nm->status_msg = "is a directory";
		return -1;
	}
	return fd;
}

void	analyze_files(t_ft_nm *ft_nm)
{
	t_list_node 	*node = ft_nm->file_list;
	char			*file_path;
	int				fd;

	ft_nm->file_list_len = ft_list_size(ft_nm->file_list);

	//loop file list
	while (node)
	{
		file_path = (char*)node->content;
		ft_nm->file_name = file_path;
		/* open */
		fd = open_file(ft_nm);
		if (fd == -1)
			put_file_error(ft_nm, file_path);
		else
		{
			/* mmmap */
			if (set_mmap(ft_nm, fd) != -1)
			{
				/* header */
				//if (node_num >= 2)
				//	ft_printf("\n%s:\n", file_path);

				set_end_offset(ft_nm);
				parse_elf_header(ft_nm);			
				/* munmap */
				munmap(ft_nm->file_head, ft_nm->file_size);
				if (ft_nm->status != NM_STATUS_0)
					put_nm_error(ft_nm); //put error and reset error flag
			}
			else //error
			{
				;
			}
		}
		node = node->next;
		close(fd);
	}
}
