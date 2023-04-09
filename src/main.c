#include "ft_nm.h"

void	init_nm(t_ft_nm *ft_nm, int argc, char **argv)
{DEBUG_PRINT;

	ft_nm->status = NM_STATUS_0;
	ft_nm->argc = argc;
	ft_nm->argv = argv;
}

int		main(int argc, char *argv[])
{DEBUG_PRINT;
	
	t_ft_nm		ft_nm;

	init_nm(&ft_nm, argc, argv);
	read_option(&ft_nm);

	return ft_nm.status;
}
