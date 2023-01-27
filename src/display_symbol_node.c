#include "../includes/ft_nm.h"
#include "../includes/elf.h"


void	display_symbol_node_64(void *content)
{
	t_sh_node_64	*node = (t_sh_node_64*)content;
	Elf64_Sym		*symbol = node->symbol;
	
	//adress ?
	if (symbol->st_value != 0)
		ft_puthex(symbol->st_value, 16, 1);
	else
		ft_putstr("                "); //x16

	printf(" ");
	printf("%s\n", node->d->sym_name_tab_ptr + node->symbol->st_name);
}
