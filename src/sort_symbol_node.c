#include "../includes/ft_nm.h"
#include "../includes/elf.h"


int		sort_symbol_node_64(void *c1, void *c2)
{
	t_sh_node_64	*node1 = (t_sh_node_64*)c1;
	t_sh_node_64	*node2 = (t_sh_node_64*)c2;
	Elf64_Sym		*symbol1 = node1->symbol;
	Elf64_Sym		*symbol2 = node2->symbol;
	char			*str1 = node1->d->sym_name_tab_ptr + symbol1->st_name;
	char			*str2 = node1->d->sym_name_tab_ptr + symbol2->st_name;

	//cmp symbol name
	int				ret = ft_strcmp(str1, str2);

	if (ret != 0)
		return ret;
	//comp address
	return symbol1->st_value - symbol2->st_value;
}
