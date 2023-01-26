#include "../includes/ft_nm.h"
#include "../includes/elf.h"

void	print_arg_error(t_ft_nm *ft_nm, t_option *op, int bit, const char *message)
{
	if (op->option_bit & bit)
	{
		ft_putstr("ft_nm: for the ");
		ft_putstr(message);
		ft_putstr(" option: may only occur zero or one times!\n");
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
			print_arg_error(ft_nm, op, OPTION_BIT_a, "-debug-syms");
		else if (*arg == 'g')
			op->option_bit |= OPTION_BIT_g;
		else if (*arg == 'u')
			print_arg_error(ft_nm, op, OPTION_BIT_u, "-undefined-only");
		else if (*arg == 'r')
			print_arg_error(ft_nm, op, OPTION_BIT_r, "-reverse-sort");
		else if (*arg == 'p')
			print_arg_error(ft_nm, op, OPTION_BIT_p, "-no-sort");
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
		index++;
	}
	if (op.option_error == 1)
		ft_nm->status = 1;
}


const char	default_input_file[] = "parse_files/ELF/hello";

void	read_option(t_ft_nm *ft_nm, int argc, char *argv[])
{
	(void)argc;

	set_option(ft_nm, 1, argv);

	if (ft_nm->file_list == NULL)
		ft_list_add_back_raw(&ft_nm->file_list, (char*)default_input_file);
}
