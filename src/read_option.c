#include "../includes/ft_nm.h"
#include "../includes/elf.h"

void	print_arg_error(t_ft_nm *ft_nm, t_option *op, int bit, const char *message)
{
	if (op->option_bit & bit)
	{
		ft_putstr("ft_nm: for the ");
		ft_putstr(message);
		ft_putstr(": may only occur zero or one times!\n");
		op->option_error = 1;
	}
	else
		op->option_bit |= bit;

	(void)ft_nm;
}

int		scan_arg_as_option(t_ft_nm *ft_nm, t_option *op, char *arg)
{
	int		hyphen_num = 0;
	int		scan_success_num = 0;

	while (*arg)
	{
		if (*arg != '-')
			break ;
		arg++;
		hyphen_num++;
	}
	while (*arg)
	{
		if (*arg == 'a')
			print_arg_error(ft_nm, op, OPTION_BIT_a, "-debug-syms option");
		else if (*arg == 'g')
			op->option_bit |= OPTION_BIT_g;
		else if (*arg == 'u')
			print_arg_error(ft_nm, op, OPTION_BIT_u, "-undefined-only option");
		else if (*arg == 'r')
			print_arg_error(ft_nm, op, OPTION_BIT_r, "-reverse-sort option");
		else if (*arg == 'p')
			print_arg_error(ft_nm, op, OPTION_BIT_p, "-no-sort option");
		else
			return 1;
		arg++;
		scan_success_num++;
	}
	if (scan_success_num == 0)
		return 1;
	return 0;
}

void	scan_arg_as_file(t_ft_nm *ft_nm, t_option *op, char *arg)
{
	printf("file: %s\n", arg);

	ft_list_add_back_raw(&ft_nm->file_list, arg);

	(void)ft_nm;
	(void)op;

}

void	scan_arg(t_ft_nm *ft_nm, t_option *op, char *arg)
{
	char	*arg_head = arg;

	if (*arg == '-')
	{
		if (scan_arg_as_option(ft_nm, op, arg) == 1)//error
		{
			op->option_error = 1;
			ft_putstr("ft_nm: Unknown command line argument '");
			ft_putstr(arg_head);
			ft_putstr("'.\n");
		}
	}
	else
	{
		scan_arg_as_file(ft_nm, op, arg);
	}
}

void	set_option(t_ft_nm *ft_nm, int index, char *argv[])
{
	t_option	op;

	op.option_bit = 0;
	op.option_error = 0;
	op.scan_bit = 0;

	while (argv[index])
	{
		scan_arg(ft_nm, &op, argv[index]);

		//if (op.duplicate_bit)
		//	return ;
		index++;
	}

	(void)ft_nm;
}


const char	default_input_file[] = "parse_files/ELF/hello";

void	read_option(t_ft_nm *ft_nm, int argc, char *argv[])
{
	//set default file name
	if (argc == 1)
	{
		ft_nm->file_name = (char*)default_input_file;
		return ;
	}
	
	// loop argv
	set_option(ft_nm, 1, argv);

	ft_list_show(ft_nm->file_list, ft_list_show_func_ptr_str);

	(void)ft_nm;
	(void)argc;
	(void)argv;

}
