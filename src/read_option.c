/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_option.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:21:33 by tkodai            #+#    #+#             */
/*   Updated: 2023/04/09 20:56:09 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	scan_arg_as_file(t_ft_nm *ft_nm, char *file_name)
{DEBUG_PRINT;
	ft_list_add_back_raw(&ft_nm->file_list, file_name);
}

void	scan_arg(t_ft_nm *ft_nm, char *arg)
{DEBUG_PRINT;
	printf("%s\n", arg);
	
	if (*arg == '-')//option
	{
	
	}
	else//scan file
	{
		scan_arg_as_file(ft_nm, arg);
	}
}

void	set_option(t_ft_nm *ft_nm)
{DEBUG_PRINT;
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
{DEBUG_PRINT;
	set_option(ft_nm);
}
