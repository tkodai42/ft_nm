#include "../includes/ft_nm.h"
#include "../includes/elf.h"

void	print_symbol_bind(int num)
{
	num = ELF64_ST_BIND(num);
	if (num == STB_LOCAL)
		ft_putstr("L :");
	if (num == STB_GLOBAL)
		ft_putstr("G :");
	if (num == STB_WEAK)
		ft_putstr("W :");
}

void	print_symbol_type(int num)
{
	//#define STT_NOTYPE	0		/* Symbol type is unspecified */
	//#define STT_OBJECT	1		/* Symbol is a data object */
	//#define STT_FUNC		2		/* Symbol is a code object */
	//#define STT_SECTION	3		/* Symbol associated with a section */
	//#define STT_FILE		4		/* Symbol's name is file name */
	//#define STT_COMMON	5		/* Symbol is a common data object */
	//#define STT_TLS		6		/* Symbol is thread-local data object*/
	//#define STT_NUM		7		/* Number of defined types.  */
	//#define STT_LOOS		10		/* Start of OS-specific */
	//#define STT_GNU_IFUNC	10		/* Symbol is indirect code object */
	//#define STT_HIOS		12		/* End of OS-specific */
	//#define STT_LOPROC	13		/* Start of processor-specific */
	//#define STT_HIPROC	15		/* End of processor-specific */


	num = ELF64_ST_TYPE(num);


	if (num == STT_NOTYPE)
		ft_putstr("NOTYPE ");
	else if (num == STT_OBJECT)
		ft_putstr("OBJECT ");
	else if (num == STT_FUNC)
		ft_putstr("FUNC   ");
	else if (num == STT_SECTION)
		ft_putstr("SECTION");
	else if (num == STT_FILE)
		ft_putstr("FILE   ");
	else if (num == STT_LOPROC)
		ft_putstr("LOPROC ");
	else if (num == STT_HIPROC)
		ft_putstr("HIPROC ");
	else
		ft_putstr("       ");

	//==========

}



char	get_symbol_type_64(t_sh_node_64 *node, Elf64_Sym *symbol)
{
	char	c = '?';

	(void)node;
	(void)symbol;
	return c;
}

void	print_symbol(t_sh_node_64 *node, Elf64_Sym *symbol)
{
	char	c;

	c = get_symbol_type_64(node, symbol);
	//size + 'z' - 'Z';

	ft_putchar(c);
	ft_putchar(' ');
}

void	display_symbol_node_64(void *content)
{
	t_sh_node_64	*node = (t_sh_node_64*)content;
	Elf64_Sym		*symbol = node->symbol;
	
	//adress ?
	//if (symbol->st_value != 0)
		ft_puthex(symbol->st_value, 16, 0);
	//else
	//	ft_putstr("                "); //x16
	ft_putstr(" ");
	
	//???
	print_symbol(node, symbol);

	//symbol bind
	print_symbol_bind(symbol->st_info);

	//symbol type
	print_symbol_type(symbol->st_info);
	ft_putstr(":");

	//symbol name
	Elf64_Shdr	*shdr = node->d->shdr_head + symbol->st_shndx;

	ft_putstr("[");
	if (symbol->st_shndx != SHN_ABS)//上限チェック
		ft_putstr(node->d->sh_name_tab_ptr + shdr->sh_name);
	ft_putstr("]");
	
	//section name
	ft_putstr(" ");
	if (node->symbol->st_name == 0)
	{
		//if (symbol->st_shndx != SHN_ABS)//上限チェック
		//	ft_putstr(node->d->sh_name_tab_ptr + shdr->sh_name);
	}
	else
		ft_putstr(node->d->sym_name_tab_ptr + node->symbol->st_name);
	ft_putstr("\n");
}
