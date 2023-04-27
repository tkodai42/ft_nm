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
	if (ft_nm->file_end < ptr || ptr < ft_nm->file_head)
	{
		ft_nm->status = NM_MEM_SEGFALULT;
		return 0;
	}
	return 1;
}

/*
 * FILE_ERROR
 */
void	put_file_linux_error(t_ft_nm *ft_nm, const char *file_path)
{
	ft_dprintf(2, "ft_nm: '%s' : %s\n", file_path, ft_nm->status_msg);

	//ft_putstr_fd("nm: ", 2);
	//ft_putstr_fd("'", 2);
	//ft_putstr_fd(file_path, 2);
	//ft_putstr_fd("'", 2);
	//ft_dprintf(2, ": %s\n", strerror(errno));
	//ft_putstr_fd(": No such file\n", 2);
	//nm: 'a': No such file
}


void	put_file_error(t_ft_nm *ft_nm, const char *file_path)
{
	ft_nm->ret_status = 1;
	if (NM_LINUX)
	{
		put_file_linux_error(ft_nm, file_path);
		return ;
	}
	ft_putstr_fd(ES_WORD_RED, 2);	
	ft_putstr_fd(ES_BOLD, 2);	
	ft_putstr_fd("error: ", 2);	
	ft_putstr_fd(ES_RESET, 2);	
	ft_putstr_fd(file_path, 2);	
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(".\n", 2);
}

/*
 * ERROR
 */

void	put_nm_error_msg(const char *file_path, const char *msg)
{
	ft_putstr_fd(ES_WORD_RED, 2);	
	ft_putstr_fd(ES_BOLD, 2);	
	ft_putstr_fd("error: ", 2);	
	ft_putstr_fd(ES_RESET, 2);	
	ft_putstr_fd(file_path, 2);	
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(".\n", 2);
}

void	put_nm_linux_error_msg(const char *file_name, const char *msg)
{
	ft_dprintf(2, "ft_nm: %s: %s\n", file_name, msg);
	//ft_putstr_fd("nm: ", 2);
	//ft_putstr_fd(file_name, 2);
	//ft_putstr_fd(": ", 2);
	//ft_putstr_fd(msg, 2);
	//ft_putstr_fd("\n", 2);
}

void	put_nm_error(t_ft_nm *ft_nm)
{
	ft_nm->ret_status = 1;
	if (NM_LINUX)
	{
		if (ft_nm->status == NM_NO_SYMBOL)
		{
			ft_nm->ret_status = 0;
			ft_nm->status = NM_STATUS_0;
			put_nm_linux_error_msg(ft_nm->file_name, "no symbols");
			return ;
		}
		put_nm_linux_error_msg(ft_nm->file_name, "file format not recognized");
		ft_nm->status = NM_STATUS_0;
		return ;
	}
	//???
	if (ft_nm->status == NM_MEM_SEGFALULT)
		put_nm_error_msg(ft_nm->file_name, "section table goes past the end of file");
	else if (ft_nm->status == NM_HDR_ERROR)
		put_nm_error_msg(ft_nm->file_name, "The file was not recognized as a valid object file");
	else if (ft_nm->status == NM_ERROR_MSG)
		put_nm_error_msg(ft_nm->file_name, ft_nm->status_msg);
	else
		put_nm_error_msg(ft_nm->file_name, "putain(unknown error)");

	ft_nm->status = NM_STATUS_0;
}
