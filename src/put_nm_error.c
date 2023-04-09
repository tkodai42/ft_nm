#include "ft_nm.h"

/*
 * OFFSET CHECK
 */
void	set_end_offset(t_ft_nm *ft_nm)
{
	ft_nm->file_end = ft_nm->file_head + ft_nm->file_size;
}

int		is_valid_offset(t_ft_nm *ft_nm, void *ptr)	
{
	if (ft_nm->file_end < ptr)
	{
		ft_nm->status = NM_MEM_SEGFALULT;
		return 0;
	}
	return 1;
}

/*
 * FILE_ERROR
 */
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

void	put_nm_error_msg(const char *file_path, const char *msg)
{
	ft_putstr_fd(ES_WORD_RED, 2);	
	ft_putstr_fd(ES_BOLD, 2);	
	ft_putstr_fd("error: ", 2);	
	ft_putstr_fd(ES_RESET, 2);	
	ft_putstr_fd(file_path, 2);	
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(".\n", 2);
}

void	put_nm_error(t_ft_nm *ft_nm)
{
	//???
	put_nm_error_msg(ft_nm->file_name, "section table goes past the end of file\n");

	ft_nm->status = NM_STATUS_0;

	//if malloc error -> dont reset to 0
}
