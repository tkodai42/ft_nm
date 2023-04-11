#include "ft_nm.h"
#include "../includes/elf.h"

//0000000000001135 T main
void	display_symbol_node_64(void *content)
{
	t_sym_node64	*node = (t_sym_node64 *)content;
	
	//address => "0000000000001135"
	ft_puthex(node->sym->st_value, 16, 0);

	//space => ' '
	ft_putchar(' ');

	//symbol type => 'T'
		
	//space => ' '
	ft_putchar(' ');

	//symbol name => "main"
	if (node->sym_name_ptr != NULL)
		ft_putstr(node->sym_name_ptr);

	ft_putchar('\n');
}
