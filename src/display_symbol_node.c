#include "ft_nm.h"
#include "../includes/elf.h"

char	get_symbol(t_sym_node64 *node)
{
	int	bind = ELF64_ST_BIND(node->sym->st_info);
	int type = ELF64_ST_TYPE(node->sym->st_info);
	int shdr_type = SHN_ABS;
	int shdr_flag = 0;

	if (node->shdr)
	{
		shdr_type = node->shdr->sh_type;
		shdr_flag = node->shdr->sh_flags;
	}
	
	if (bind == STB_WEAK)
	{
		if (shdr_type == SHT_PROGBITS)
			return 'W';
		return 'w';
	}
	if ((shdr_flag & SHF_WRITE && shdr_flag & SHF_ALLOC))
	{
		if (shdr_type == SHT_NOBITS)
		{
			if (bind == STB_GLOBAL)
				return 'B';
			return 'b';
		}
		if (1) //linux
		{
			if (shdr_type == SHT_PROGBITS || shdr_type == SHT_DYNAMIC || shdr_type == SHT_INIT_ARRAY || shdr_type == SHT_FINI_ARRAY)
			{
				if (bind == STB_GLOBAL)
					return 'D';
				return 'd';	
			}
		}
		else //max os
		{
			if (shdr_type == SHT_PROGBITS || shdr_type == SHT_DYNAMIC)
			{
				if (bind == STB_GLOBAL)
					return 'D';
				return 'd';	
			}
		}
	}
	if (shdr_type == SHN_ABS)
	{
		return 'a';//65521 SHN_ABS
	}
	if (shdr_type == SHT_PROGBITS && shdr_flag == SHF_ALLOC)
	{
		if (bind == STB_GLOBAL)
			return 'R';
		return 'r';
	}
	if (shdr_type == SHT_NULL)
	{
		//if (bind == STB_GLOBAL) //????
			return 'U';
		//return 'u';
	}
	if (1)//linux
	{
		if (shdr_flag & SHF_MERGE && shdr_flag & SHF_STRINGS)
			return 'n';
		if (type == STT_SECTION && shdr_type == SHT_PROGBITS && shdr_flag == 0)
			return 'n';
	}
	if (shdr_type == SHT_PROGBITS && shdr_flag & SHF_ALLOC && shdr_flag & SHF_EXECINSTR)
	{
		if (bind == STB_GLOBAL)
			return 'T';
		return 't';
	}
	if (shdr_flag & SHF_WRITE && shdr_flag & SHF_ALLOC)
	{
		if (bind == STB_GLOBAL)
			return 'T';
		return 't';
	}
	if (1) //linux
	{
		if ((shdr_flag == SHF_ALLOC) || (shdr_flag & SHF_ALLOC && shdr_flag & SHF_INFO_LINK))
			return 'r';
	}
	return '?';
}

int		is_hidden_symbol(t_sym_node64 *node)
{
	char	symbol_type = get_symbol(node);
	int		bind = ELF64_ST_BIND(node->sym->st_info);
	int		type = ELF64_ST_TYPE(node->sym->st_info);


	//delete (STB_LOCAL && STT_NOTYPE && SHT_NULL && U)
	if (bind == STB_LOCAL && type == STT_NOTYPE && node->shdr && node->shdr->sh_type == SHT_NULL && symbol_type == 'U')
		return 1;

	if (NM_OPTION_u(node->ft_nm->option.flag_bit))
	{
		if (symbol_type == 'u' || symbol_type == 'U' || symbol_type == 'w')
			;
		else
			return 1;
	}
	if (NM_OPTION_a(node->ft_nm->option.flag_bit) == 0)
	{
		if (ft_strlen(node->sym_name_ptr) == 0)
			return 1;
		if (symbol_type == 'a')
			return 1;
	}
	if (NM_OPTION_g(node->ft_nm->option.flag_bit))
	{
		if (bind == STB_LOCAL)
			return 1;
	}
	return 0;
}

//0000000000001135 T main
void	display_symbol_node_64(void *content)
{
	t_sym_node64	*node = (t_sym_node64 *)content;
	char			symbol_type = get_symbol(node);
	

	if (is_hidden_symbol(node) == 1)
		return ;

	//address => "0000000000001135"
	if (node->sym->st_value == 0 && (node->shdr && node->shdr->sh_type == SHT_NULL))
	{
		for (int i = 0; i < 16; i++)
			ft_putchar(' ');
	}
	else
		ft_puthex(node->sym->st_value, 16, 0);

	if (NM_DEBUG)//debug
	{
		debug_print_symbol_bind(ELF64_ST_BIND(node->sym->st_info));
		debug_print_symbol_type(ELF64_ST_TYPE(node->sym->st_info));
		debug_print_section_type(node->shdr ? node->shdr->sh_type : SHN_ABS);
		debug_print_section_flags(node->shdr ? node->shdr->sh_flags: 0);
		ft_printf("%13s |", get_section_name(node->ft_nm, node->shdr));
	}

	//space => ' '
	ft_putchar(' ');

	//symbol type => 'T'
	ft_putchar(symbol_type);
		
	if (NM_DEBUG) //debug
		ft_putstr(" |");
	//space => ' '
	ft_putchar(' ');

	//symbol name => "main"
	if (node->sym_name_ptr != NULL)
		ft_putstr(node->sym_name_ptr);

	ft_putchar('\n');
}
