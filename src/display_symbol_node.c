#include "ft_nm.h"
#include "../includes/elf.h"


void	debug_print_symbol_type(int type)
{
	ft_putstr(" [");
	if (STT_NOTYPE == type)
		ft_putstr("STT_NOTYPE");
	else if (STT_OBJECT == type)
		ft_putstr("STT_OBJECT");
	else if (STT_FUNC == type)
		ft_putstr("STT_FUNC");
	else if (STT_SECTION == type)
		ft_putstr("STT_SECTION");
	else if (STT_FILE == type)
		ft_putstr("STT_FILE");
	else if (STT_COMMON == type)
		ft_putstr("STT_COMMON");
	else if (STT_TLS == type)
		ft_putstr("STT_TLS");
	else if (STT_LOOS == type)
		ft_putstr("STT_LOOS");
	else if (STT_HIOS == type)
		ft_putstr("STT_HIOS");
	else if (STT_LOPROC == type)
		ft_putstr("STT_LOPROC");
	else if (STT_SPARC_REGISTER == type)
		ft_putstr("STT_SPARC_REGISTER");
	else if (STT_HIPROC == type)
		ft_putstr("STT_HIPROC");
	
	ft_putstr("] ");
}

void	debug_func(t_sym_node64 *node)
{

	ft_putstr(" [");
		
	ft_putstr(get_section_name(node->ft_nm, node->shdr));
	ft_putstr("] ");
}

char	get_symbol(t_sym_node64 *node)
{
	if (ft_strcmp(".text", node->shdr_name_ptr) == 0)	
		return 't';
	if (ft_strcmp(".bss", node->shdr_name_ptr) == 0)	
		return 'b';
	if (ft_strcmp(".data", node->shdr_name_ptr) == 0)	
		return 'd';

	return ' ';
}

//0000000000001135 T main
void	display_symbol_node_64(void *content)
{
	t_sym_node64	*node = (t_sym_node64 *)content;
	
	//address => "0000000000001135"
	ft_puthex(node->sym->st_value, 16, 0);

	//space => ' '
	ft_putchar(' ');

	//symbol type => 'T'
	ft_putchar(get_symbol(node));
		
	//space => ' '
	ft_putchar(' ');

	//symbol name => "main"
	if (node->sym_name_ptr != NULL)
		ft_putstr(node->sym_name_ptr);

	if (1)
	{
		debug_func(node);
		debug_print_symbol_type(ELF64_ST_TYPE(node->sym->st_info));
	}

	ft_putchar('\n');
}
