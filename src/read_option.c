/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_option.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:21:33 by tkodai            #+#    #+#             */
/*   Updated: 2023/04/09 20:36:01 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	scan_arg(t_ft_nm *ft_nm, char *arg)
{DEBUG_PRINT;
	(void)ft_nm;
	(void)arg;
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
