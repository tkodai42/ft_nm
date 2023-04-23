/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_option.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:21:33 by tkodai            #+#    #+#             */
/*   Updated: 2023/04/24 04:51:13 by tkodai           ###   ########.fr       */
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

char	*scan_arg_as_option(t_ft_nm *ft_nm, char *arg)
{
	int		scan_success_num = 0;

	//skip '-'
	arg++;
	
	while (*arg)
	{
		if (NM_LINUX)
		{
			if (*arg == 'a')
				ft_nm->option.flag_bit |= OPTION_BIT_a;
			else if (*arg == 'g')
				ft_nm->option.flag_bit |= OPTION_BIT_g;
			else if (*arg == 'u')
				ft_nm->option.flag_bit |= OPTION_BIT_u;
			else if (*arg == 'r')
				ft_nm->option.flag_bit |= OPTION_BIT_r;
			else if (*arg == 'p')
				ft_nm->option.flag_bit |= OPTION_BIT_p;
			else if (*arg == 'h')
			{
				ft_nm->option.flag_bit |= OPTION_BIT_h;
				return NULL;
			}
			else//invalid + h
			{
				ft_nm->option.flag_bit |= OPTION_BIT_h;
				return arg;
			}
		}
		else //mac
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
			else if (*arg == 'h')
				ft_nm->option.flag_bit |= OPTION_BIT_h;
			else //unknown option
				return "putain";
		}
		arg++;
		scan_success_num++;
	}
	if (scan_success_num == 0)
		return "putain";
	return NULL;
}

void	scan_arg_as_file(t_ft_nm *ft_nm, char *file_name)
{
	ft_list_add_back_raw(&ft_nm->file_list, file_name);
}

/*
 * NULL    == ok
 * 'char*' == nm: invalid option -- 'z'
 *  ???       nm: unrecognized option '---aaaasdf' <---- putain
 */
void	scan_arg(t_ft_nm *ft_nm, char *arg)
{
	char	*ret;

	if (*arg == '-' && ft_strlen(arg) != 1)//option //in linux [-] file [--] ok [---] putain
	{
		ret = scan_arg_as_option(ft_nm, arg);
		if (ret != NULL && NM_LINUX == 0)
		{
			ft_nm->status = NM_ARG_OPTION_ERROR;
			ft_putstr_fd("ft_nm: Unknown command line argument '", 2);		
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("'.\n", 2);
			return ;
		}
		/* LINUX */
		else if (ret != NULL)
		{
			ft_nm->status = NM_ARG_OPTION_ERROR;
			ft_nm->ret_status = 1;
			ft_dprintf(2, "ft_nm: invalid option -- \'%c\'\n", *ret);
			return ;
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
		if (NM_OPTION_h(ft_nm->option.flag_bit))
			return ;
		index++;
	}
}

void	read_option(t_ft_nm *ft_nm)
{
	set_option(ft_nm);

	if (ft_nm->status != NM_STATUS_0)
		ft_nm->ret_status = 1;

	if (NM_OPTION_h(ft_nm->option.flag_bit))
	{	
		ft_nm->status = NM_PUT_HELP;
		return ;
	}

	if (ft_nm->file_list == NULL)//no files -> default
		scan_arg_as_file(ft_nm, DEFAULT_ARG_FILE);
}
