#include "../includes/ft_nm.h"
#include "../includes/elf.h"

int		is_valid_address(t_ft_nm *ft_nm, void *ptr)
{
	if (ptr == NULL)
		return 1;
	if (ptr - ft_nm->head > ft_nm->file_size)
		return 1;
	return 0;
}

void	free_nm(t_ft_nm *ft_nm)
{
	(void)ft_nm;
}

void	init_nm(t_ft_nm *ft_nm)
{
	ft_nm->status = NM_STATUS_0;
	ft_nm->head = NULL;

	//file
	ft_nm->file_name = NULL;
	ft_nm->file_list = NULL;
}

int		main(int argc, char *argv[])
{
	t_ft_nm		ft_nm;

	init_nm(&ft_nm);
	if (ft_nm.status == 0)
		read_option(&ft_nm, argc, argv);
	if (ft_nm.status == 0)
		execute(&ft_nm);
	//read_option
	//open_file

	
	(void)argc;
	(void)argv;
}
