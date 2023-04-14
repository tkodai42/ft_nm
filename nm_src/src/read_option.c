/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_option.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:21:33 by tkodai            #+#    #+#             */
/*   Updated: 2023/04/14 03:37:36 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	set_option_bit(t_ft_nm *ft_nm, int bit, const char *message)
{
	if (ft_nm->option.flag_bit & bit)
	{
		ft_putstr_fd("ft_nm: for the ", 2);
		ft_putstr_fd(message, 2);
		ft_putstr_fd(" option: may only occur zero or one times!\n", 2);
		ft_nm->status = NM_ARG_OPTION_ERROR;
	}
	else
		ft_nm->option.flag_bit |= bit;
}

//arg[0] == '-'
int		scan_arg_as_option(t_ft_nm *ft_nm, char *arg)
{
	int		scan_success_num = 0;

	while (*arg)
	{
		if (*arg != '-')
			break ;
		arg++;
	}
	while (*arg)
	{
		if (*arg == 'a')
			set_option_bit(ft_nm, OPTION_BIT_a, "-debug-syms");
		else if (*arg == 'g')
			ft_nm->option.flag_bit |= OPTION_BIT_g;
		else if (*arg == 'u')
			set_option_bit(ft_nm, OPTION_BIT_u, "-undefined-only");
		else if (*arg == 'r')
			set_option_bit(ft_nm, OPTION_BIT_r, "-reverse-sort");
		else if (*arg == 'p')
			set_option_bit(ft_nm, OPTION_BIT_p, "-no-sort");

		else //unknown option
			return 1;
		arg++;
		scan_success_num++;
	}
	if (scan_success_num == 0)
		return 1;
	return 0;
}

void	scan_arg_as_file(t_ft_nm *ft_nm, char *file_name)
{
	ft_list_add_back_raw(&ft_nm->file_list, file_name);
}

void	scan_arg(t_ft_nm *ft_nm, char *arg)
{
	if (*arg == '-')//option
	{
		if (scan_arg_as_option(ft_nm, arg) == 1)//error
		{
			ft_nm->status = NM_ARG_OPTION_ERROR;
			ft_putstr_fd("ft_nm: Unknown command line argument '", 2);		
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("'.\n", 2);
		}
	}
	else//scan file
	{
		scan_arg_as_file(ft_nm, arg);
	}
}

void	set_option(t_ft_nm *ft_nm)
{
	int		index = 1;

	//init option bits;
	ft_nm->option.flag_bit = 0;
	ft_nm->option.error = 0;
	ft_nm->option.scan_bit = 0;

	//loop args
	while (ft_nm->argv[index])
	{
		scan_arg(ft_nm, ft_nm->argv[index]);
		index++;
	}
}

void	read_option(t_ft_nm *ft_nm)
{
	set_option(ft_nm);

	if (ft_nm->file_list == NULL)//no files -> default
		scan_arg_as_file(ft_nm, DEFAULT_ARG_FILE);
}
