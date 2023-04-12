#include "ft_nm.h"
#include "../includes/elf.h"

void	debug_print_symbol_bind(int bind)
{
	//ft_putstr(" [");
	if (STB_LOCAL == bind)
		printf(" |%10s", "STB_LOCAL");
	else if (STB_GLOBAL == bind)
		printf(" |%10s", "STB_GLOBAL");
	else if (STB_WEAK == bind)
		printf(" |%10s", "STB_WEAK");
	else if (STB_LOOS == bind)
		printf(" |%10s", "STB_LOOS");
	else if (STB_HIOS == bind)
		printf(" |%10s", "STB_HIOS");
	else if (STB_LOPROC == bind)
		printf(" |%10s", "STB_LOPROC");
	else if (STB_HIPROC == bind)
		printf(" |%10s", "STB_HIPROC");
	else
		printf(" |%10s", "STT_*****");
	
	//ft_putstr("] ");
}


void	debug_print_symbol_type(int type)
{
	//ft_putstr(" [");
	if (STT_NOTYPE == type)
		printf("%13s |", "STT_NOTYPE");
	else if (STT_OBJECT == type)
		printf("%13s |", "STT_OBJECT");
	else if (STT_FUNC == type)
		printf("%13s |", "STT_FUNC");
	else if (STT_SECTION == type)
		printf("%13s |", "STT_SECTION");
	else if (STT_FILE == type)
		printf("%13s |", "STT_FILE");
	else if (STT_COMMON == type)
		printf("%13s |", "STT_COMMON");
	else if (STT_TLS == type)
		printf("%13s |", "STT_TLS");
	else if (STT_LOOS == type)
		printf("%13s |", "STT_LOOS");
	else if (STT_HIOS == type)
		printf("%13s |", "STT_HIOS");
	else if (STT_LOPROC == type)
		printf("%13s |", "STT_LOPROC");
	else if (STT_SPARC_REGISTER == type)
		printf("%13s |", "STT_SPARC_REGISTER");
	else if (STT_HIPROC == type)
		printf("%13s |", "STT_HIPROC");
	
	//ft_putstr("] ");
}

void	debug_func(t_sym_node64 *node)
{

	ft_putstr(" [");
		
	ft_putstr(get_section_name(node->ft_nm, node->shdr));
	ft_putstr("] ");
}

char	get_symbol(t_sym_node64 *node)
{
	int	bind = ELF64_ST_BIND(node->sym->st_info);

	if (bind == STB_WEAK)
		return 'w';

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

	if (1)//debug
	{
		debug_print_symbol_bind(ELF64_ST_BIND(node->sym->st_info));
		debug_print_symbol_type(ELF64_ST_TYPE(node->sym->st_info));
		//debug_print_section_type(node->symbol);
		fflush(stdout);
	}

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
		//debug_print_symbol_type(ELF64_ST_TYPE(node->sym->st_info));
		//debug_print_symbol_bind(ELF64_ST_BIND(node->sym->st_info));
	}

	ft_putchar('\n');
}
