#include "ft_nm.h"
#include "../includes/elf.h"

void	debug_print_symbol_bind(int bind)
{
	//ft_putstr(" [");
	if (STB_LOCAL == bind)
		printf(" %10s |", "STB_LOCAL");
	else if (STB_GLOBAL == bind)
		printf(" %10s |", "STB_GLOBAL");
	else if (STB_WEAK == bind)
		printf(" %10s |", "STB_WEAK");
	else if (STB_LOOS == bind)
		printf(" %10s |", "STB_LOOS");
	else if (STB_HIOS == bind)
		printf(" %10s |", "STB_HIOS");
	else if (STB_LOPROC == bind)
		printf(" %10s |", "STB_LOPROC");
	else if (STB_HIPROC == bind)
		printf(" %10s |", "STB_HIPROC");
	else
		printf(" %10s |", "");
	
	//ft_putstr("] ");
}

void	debug_print_symbol_type(int type)
{
	//ft_putstr(" [");
	if (STT_NOTYPE == type)
		printf("%12s |", "STT_NOTYPE");
	else if (STT_OBJECT == type)
		printf("%12s |", "STT_OBJECT");
	else if (STT_FUNC == type)
		printf("%12s |", "STT_FUNC");
	else if (STT_SECTION == type)
		printf("%12s |", "STT_SECTION");
	else if (STT_FILE == type)
		printf("%12s |", "STT_FILE");
	else if (STT_COMMON == type)
		printf("%12s |", "STT_COMMON");
	else if (STT_TLS == type)
		printf("%12s |", "STT_TLS");
	else if (STT_LOOS == type)
		printf("%12s |", "STT_LOOS");
	else if (STT_HIOS == type)
		printf("%12s |", "STT_HIOS");
	else if (STT_LOPROC == type)
		printf("%12s |", "STT_LOPROC");
	else if (STT_SPARC_REGISTER == type)
		printf("%12s |", "STT_SPARC_REGISTER");
	else if (STT_HIPROC == type)
		printf("%12s |", "STT_HIPROC");
	else
		printf("%12s |", "");
	
	//ft_putstr("] ");
}

void	debug_print_section_type(int type)
{
	if (SHT_NULL == type)
		printf("%14s |", "SHT_NULL");
	else if (SHT_PROGBITS == type)
		printf("%14s |", "SHT_PROGBITS");
	else if (SHT_SYMTAB == type)
		printf("%14s |", "SHT_SYMTAB");
	else if (SHT_STRTAB == type)
		printf("%14s |", "SHT_STRTAB");
	else if (SHT_RELA == type)
		printf("%14s |", "SHT_RELA");
	else if (SHT_HASH == type)
		printf("%14s |", "SHT_HASH");
	else if (SHT_DYNAMIC == type)
		printf("%14s |", "SHT_DYNAMIC");
	else if (SHT_NOTE == type)
		printf("%14s |", "SHT_NOTE");
	else if (SHT_NOBITS == type)
		printf("%14s |", "SHT_NOBITS");
	else if (SHT_REL == type)
		printf("%14s |", "SHT_REL");
	else if (SHT_SHLIB == type)
		printf("%14s |", "SHT_SHLIB");
	else if (SHT_DYNSYM == type)
		printf("%14s |", "SHT_DYNSYM");
	else if (SHT_INIT_ARRAY == type)
		printf("%14s |", "SHT_INIT_ARRAY");
	else if (SHT_FINI_ARRAY == type)
		printf("%14s |", "SHT_FINI_ARRAY");
	else if (SHT_PREINIT_ARRAY == type)
		printf("%14s |", "SHT_PREINIT_ARRAY");
	else if (SHT_GROUP == type)
		printf("%14s |", "SHT_GROUP");
	else if (SHT_SYMTAB_SHNDX == type)
		printf("%14s |", "SHT_SYMTAB_SHNDX");
	else if (SHT_NUM == type)
		printf("%14s |", "SHT_NUM");
	else if (SHT_LOOS == type)
		printf("%14s |", "SHT_LOOS");
	else
		printf("%14s |", "");
			
}

void	debug_print_section_flags(unsigned int flag)
{
	if (SHF_WRITE == flag)
		printf("%10s |", "SHF_WRITE");
	else if (SHF_ALLOC == flag)
		printf("%10s |", "SHF_ALLOC");
	else if (SHF_EXECINSTR == flag)
		printf("%10s |", "SHF_EXECINSTR");
	else if (SHF_MERGE == flag) 
		printf("%10s |", "SHF_MERGE");
	else if (SHF_STRINGS == flag)
		printf("%10s |", "SHF_STRINGS");
	else if (SHF_INFO_LINK == flag)
		printf("%10s |", "SHF_INFO_LINK");
	else if (SHF_LINK_ORDER == flag)
		printf("%10s |", "SHF_LINK_ORDER");
	else if (SHF_OS_NONCONFORMING == flag)
		printf("%10s |", "SHF_OS_NONCONFORMING");
	else if (SHF_GROUP == flag)
		printf("%10s |", "SHF_GROUP");
	else if (SHF_TLS == flag)
		printf("%10s |", "SHF_TLS");
	else if (SHF_MASKOS == flag)
		printf("%10s |", "SHF_MASKOS");
	else if (SHF_MASKPROC == flag)
		printf("%10s |", "SHF_MASKPROC");
	else if (SHF_ORDERED == flag)
		printf("%10s |", "SHF_ORDERED");
	else if (SHF_EXCLUDE == flag)
		printf("%10s |", "SHF_EXCLUDE");
	else
		printf("%10s |", "  ");
}

void	debug_func(t_sym_node64 *node)
{

	//ft_putstr(" [");
		
	//ft_putstr(get_section_name(node->ft_nm, node->shdr));
	printf("%13s |", get_section_name(node->ft_nm, node->shdr));
	//ft_putstr("] ");
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
		debug_print_section_type(node->shdr ? node->shdr->sh_type : INT_MAX);
		debug_print_section_flags(node->shdr ? node->shdr->sh_flags: INT_MAX);
		debug_func(node);
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

	ft_putchar('\n');
}
