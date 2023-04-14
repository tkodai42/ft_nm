#include "ft_nm.h"

void	init_nm(t_ft_nm *ft_nm, int argc, char **argv)
{

	ft_nm->status = NM_STATUS_0;
	ft_nm->argc = argc;
	ft_nm->argv = argv;
	//file
	ft_nm->file_list = NULL;
}

int		main(int argc, char *argv[])
{
	
	t_ft_nm		ft_nm;

	init_nm(&ft_nm, argc, argv);
	read_option(&ft_nm);
	if (ft_nm.status != NM_STATUS_0)
		return 1;

	execute_nm(&ft_nm);	

	system("leaks ft_nm");
	return ft_nm.status;
}
