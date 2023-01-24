#include "../includes/ft_nm.h"
#include "../includes/elf.h"

void	free_nm(t_ft_nm *ft_nm)
{
	(void)ft_nm;
}

void	init_nm(t_ft_nm *ft_nm)
{
	ft_nm->status = NM_STATUS_0;
	ft_nm->head = NULL;

	//file
	ft_nm->fd = -1;
	ft_nm->file_name = NULL;
	ft_nm->file_list = NULL;
}

int		main(int argc, char *argv[])
{
	printf(" === FT_NM ===\n");

	t_ft_nm		ft_nm;

	init_nm(&ft_nm);
	if (ft_nm.status == 0)
		read_option(&ft_nm, argc, argv);
	//read_option
	//open_file

	
	(void)argc;
	(void)argv;
}
