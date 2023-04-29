#include "ft_nm.h"
#include "../includes/elf.h"

char	get_symbol(t_sym_node *node)
{
	int	bind;
	int type;
	int shdr_type = SHN_ABS;
	int shdr_flag = 0;


	if (node->ft_nm->is_64)
	{
		bind = ELF64_ST_BIND(node->sym64->st_info);
		type = ELF64_ST_TYPE(node->sym64->st_info);
		if (node->shdr64)
		{
			shdr_type = node->shdr64->sh_type;
			shdr_flag = node->shdr64->sh_flags;
		}
	}
	else
	{
		bind = ELF32_ST_BIND(node->sym32->st_info);
		type = ELF32_ST_TYPE(node->sym32->st_info);
		if (node->shdr32)
		{
			shdr_type = node->shdr32->sh_type;
			shdr_flag = node->shdr32->sh_flags;
		}
	}
	
	if (bind == STB_WEAK)
	{
		if (type == STT_OBJECT)
			return 'v';
		if (shdr_type == SHT_PROGBITS || shdr_type == SHT_NOBITS)
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
		if (NM_LINUX)
		{
			if (shdr_type == SHT_PROGBITS || shdr_type == SHT_PREINIT_ARRAY
				|| shdr_type == SHT_DYNAMIC || shdr_type == SHT_INIT_ARRAY || shdr_type == SHT_FINI_ARRAY)
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
	if (shdr_type == SHT_PROGBITS && (shdr_flag == SHF_ALLOC || (shdr_flag & SHF_ALLOC && shdr_flag & SHF_MERGE)))
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
	if (NM_LINUX)
	{
		if (strcmp(node->shdr_name_ptr, ".comment") == 0)
			return 'n';


		if (bind == STB_LOCAL && type == STT_SECTION && shdr_type == SHT_PROGBITS && shdr_flag == 0)
		{
			if (strncmp(node->shdr_name_ptr, ".debug_", ft_strlen(".debug_")) == 0)
				return 'N';
			return 'n';
		}

		//if (shdr_flag & SHF_MERGE && shdr_flag & SHF_STRINGS)
		//	return 'n';
		if (type == STT_SECTION && shdr_type == SHT_PROGBITS && shdr_flag & SHF_MERGE && shdr_flag & SHF_STRINGS)
			return 'N';
		if (type == STT_SECTION && shdr_type == SHT_PROGBITS && shdr_flag == 0)
			return 'N';
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
	if (NM_LINUX)
	{
		if ((shdr_flag == SHF_ALLOC) || (shdr_flag & SHF_ALLOC && shdr_flag & SHF_INFO_LINK))
			return 'r';
	}
	return '?';
}

int		is_hidden_symbol(t_sym_node *node)
{
	char	symbol_type = get_symbol(node);
	int		bind;
	int		type;

	if (node->ft_nm->is_64)
	{
		bind = ELF64_ST_BIND(node->sym64->st_info);
		type = ELF64_ST_TYPE(node->sym64->st_info);
	}
	else
	{
		bind = ELF32_ST_BIND(node->sym32->st_info);
		type = ELF32_ST_TYPE(node->sym32->st_info);
	}

	//delete (STB_LOCAL && STT_NOTYPE && SHT_NULL && U)
	if (node->ft_nm->is_64)
	{
		if (bind == STB_LOCAL && type == STT_NOTYPE
			&& node->shdr64 && node->shdr64->sh_type == SHT_NULL && symbol_type == 'U')
			return 1;
	}
	else
	{
		if (bind == STB_LOCAL && type == STT_NOTYPE
			&& node->shdr32 && node->shdr32->sh_type == SHT_NULL && symbol_type == 'U')
			return 1;
	}

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
	t_sym_node		*node = (t_sym_node *)content;
	char			symbol_type = get_symbol(node);
	

	if (is_hidden_symbol(node) == 1)
		return ;

	//address => "0000000000001135"
	if (node->ft_nm->is_64)
	{
		if (symbol_type == 'U' || (node->sym64->st_value == 0
			&& (node->shdr64 && node->shdr64->sh_type == SHT_NULL)))
		{
			for (int i = 0; i < 16; i++)
				ft_putchar(' ');
		}
		else
			ft_puthex(node->sym64->st_value, 16, 0);
	}
	else
	{
		if (symbol_type == 'U' || (node->sym32->st_value == 0
			&& (node->shdr32 && node->shdr32->sh_type == SHT_NULL)))
		{
			for (int i = 0; i < 8; i++)
				ft_putchar(' ');
		}
		else
			ft_puthex(node->sym32->st_value, 8, 0);
	}

	if (NM_DEBUG)//debug
	{
		if (node->ft_nm->is_64)
		{
			debug_print_symbol_bind(ELF64_ST_BIND(node->sym64->st_info));
			debug_print_symbol_type(ELF64_ST_TYPE(node->sym64->st_info));
			debug_print_section_type(node->shdr64 ? node->shdr64->sh_type : SHN_ABS);
			debug_print_section_flags(node->shdr64 ? node->shdr64->sh_flags: 0);
			ft_printf("%13s |", get_section_name(node->ft_nm, node->shdr64));
		}
		else
		{
			debug_print_symbol_bind(ELF32_ST_BIND(node->sym32->st_info));
			debug_print_symbol_type(ELF32_ST_TYPE(node->sym32->st_info));
			debug_print_section_type(node->shdr32 ? node->shdr32->sh_type : SHN_ABS);
			debug_print_section_flags(node->shdr32 ? node->shdr32->sh_flags: 0);
			ft_printf("%13s |", get_section_name(node->ft_nm, node->shdr32));
		}
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
