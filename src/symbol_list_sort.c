#include "ft_nm.h"

int		sort_symbol_node(void *c1, void *c2)
{
	t_sym_node64	*node1 = (t_sym_node64 *)c1;
	t_sym_node64	*node2 = (t_sym_node64 *)c2;
	int				ret;

	ret = ft_strcmp(node1->sym_name_ptr, node2->sym_name_ptr);

	if (ret != 0)
		return ret;

	return node1->sym->st_value - node2->sym->st_value;
}

void	ft_symbol_list_sort(t_ft_nm *ft_nm)
{
	if (NM_OPTION_p(ft_nm->option.flag_bit))//no sort
		return ;
	if (NM_OPTION_r(ft_nm->option.flag_bit))
		ft_list_sort(&ft_nm->symbol_list, sort_symbol_node, 1);//rev
	else
		ft_list_sort(&ft_nm->symbol_list, sort_symbol_node, 0);
}
