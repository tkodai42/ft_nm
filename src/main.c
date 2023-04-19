#include "ft_nm.h"

#if 0
__attribute__((destructor))
void    destructor(void)
{
	system("leaks ft_nm");
}
#endif

int		nm_destructor(t_ft_nm *ft_nm)
{
	ft_list_clear(&ft_nm->file_list, NULL);
	ft_list_clear(&ft_nm->symbol_list, NULL);
	exit(ft_nm->status);
	return ft_nm->status;
}

void	init_nm(t_ft_nm *ft_nm, int argc, char **argv)
{
	ft_nm->status = NM_STATUS_0;
	ft_nm->argc = argc;
	ft_nm->argv = argv;
	//file
	ft_nm->file_list = NULL;
	ft_nm->symbol_list = NULL;
}

int		main(int argc, char *argv[])
{
	t_ft_nm		ft_nm;

	init_nm(&ft_nm, argc, argv);
	read_option(&ft_nm);
	if (ft_nm.status != NM_STATUS_0)
		return 1;

	execute_nm(&ft_nm);	
	return nm_destructor(&ft_nm);
}
