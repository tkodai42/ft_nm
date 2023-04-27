#include "ft_nm.h"
#include "../includes/elf.h"

int		scan_fh_magic_number_ELF(t_ft_nm *ft_nm, Elf64_Ehdr *ehdr_64)
{
	if (ehdr_64->e_ident[EI_MAG0] != 0x7F)
	{
		ft_nm->status = NM_HDR_ERROR;
		return 0;
	}
	if (ft_strncmp("ELF", (char *)&(ehdr_64->e_ident[EI_MAG1]), 3) != 0)
	{
		ft_nm->status = NM_HDR_ERROR;
		return 0;
	}
	return 1;
}

int		set_bit_format(t_ft_nm *ft_nm, Elf64_Ehdr *ehdr_64)
{
	int		format = ehdr_64->e_ident[EI_CLASS];

	if (format == 1)
		ft_nm->is_64 = 0;
	else if (format == 2)
		ft_nm->is_64 = 1;
	else
	{
		ft_nm->status = NM_HDR_ERROR;
		return 0;
	}
	return 1;
}


int		check_section_offset(t_ft_nm *ft_nm)
{
	Elf64_Shdr	*shdr_64;
	Elf32_Shdr	*shdr_32;
	int			section_size = get_sections_size(ft_nm);
	int			section_index = 0;

	if (ft_nm->is_64)
		shdr_64 = get_sections_offset(ft_nm);
	else
		shdr_32 = get_sections_offset(ft_nm);

	if (section_size < 0)
	{
		ft_nm->status_msg = "SECTION NUM IS INVALID";
		ft_nm->status = NM_ERROR_MSG;
		return 0;
	}
	//check all section
	while (section_index < section_size)
	{
		if (ft_nm->is_64)
		{
			//セクションのオフセットの位置が有効？
			if (is_valid_offset(ft_nm, (void*)shdr_64 + sizeof(Elf64_Shdr)) == 0)	
				return 0;
			//セクションのオフセットからimage sizeが有効？head+offset+image size
			if (is_valid_offset(ft_nm, ft_nm->file_head
						+ shdr_64->sh_offset + shdr_64->sh_size) == 0)
				return 0;

			shdr_64++;
		}
		else
		{
			if (is_valid_offset(ft_nm, (void*)shdr_32 + sizeof(Elf32_Shdr)) == 0)	
				return 0;
			if (is_valid_offset(ft_nm, ft_nm->file_head
						+ shdr_32->sh_offset + shdr_32->sh_size) == 0)
				return 0;

			shdr_32++;
		}

		if (NM_DEBUG)
		{
			const char *ptr = get_section_name(ft_nm, shdr_64);

			ft_printf("%s\n", ptr);
			if (shdr_64->sh_type == SHT_STRTAB)
				ft_printf("tab\n");
		}
		section_index++;
	
	}
	return 1;
}

void	scan_file_header(t_ft_nm *ft_nm, Elf64_Ehdr *ehdr_64)
{			
	if (is_valid_offset(ft_nm, ft_nm->file_head + sizeof(Elf64_Ehdr)) == 0)
		return ;

	/* scan 0x7F E L F */		
	if (scan_fh_magic_number_ELF(ft_nm, ehdr_64) == 0)
		return ;

	/* scan 32 or 64 */
	if (set_bit_format(ft_nm, ehdr_64) == 0)
		return ;

	/* check */
	if (check_section_offset(ft_nm) == 0)
		return ;
}

void	generate_symbol_list(t_ft_nm *ft_nm)
{
	Elf64_Shdr	*symbol_section64;
	Elf64_Sym	*sym64;
	Elf32_Shdr	*symbol_section32;
	Elf32_Sym	*sym32;
	int			sym_size;
	int			sym_index = 0;

	if (ft_nm->is_64)
	{
		symbol_section64 = get_section_by_type(ft_nm, SHT_SYMTAB);
		sym64 = ft_nm->file_head + symbol_section64->sh_offset;
		sym_size = symbol_section64->sh_size / sizeof(Elf64_Sym); 
	}
	else
	{
		symbol_section32 = get_section_by_type(ft_nm, SHT_SYMTAB);
		sym32 = ft_nm->file_head + symbol_section32->sh_offset;
		sym_size = symbol_section32->sh_size / sizeof(Elf32_Sym); 
	}

	while (sym_index < sym_size)
	{
		/* generate node */
		t_sym_node	*node = malloc(sizeof(t_sym_node));

		if (node == NULL)
			ft_put_error_msg_exit("malloc");
		/* set */
		if (ft_nm->is_64)
		{
			node->sym64 = sym64;
			node->shdr64 = get_section_by_sym(ft_nm, sym64);
			node->ft_nm = ft_nm;
			node->sym_name_ptr = get_symbol_name(ft_nm, sym64);
			node->shdr_name_ptr = get_section_name(ft_nm, node->shdr64);
		}
		else
		{
			node->sym32 = sym32;
			node->shdr32 = get_section_by_sym(ft_nm, sym32);
			node->ft_nm = ft_nm;
			node->sym_name_ptr = get_symbol_name(ft_nm, sym32);
			node->shdr_name_ptr = get_section_name(ft_nm, node->shdr32);
		}
		if (NM_LINUX)
		{
			if (node->sym_name_ptr == NULL)
			{
				if (NM_OPTION_a(node->ft_nm->option.flag_bit))
					node->sym_name_ptr = node->shdr_name_ptr;
			}
			if (node->sym_name_ptr == NULL)
				node->sym_name_ptr = "";
		}
		//ft_printf("%s\n", get_symbol_name(ft_nm, sym));
		ft_list_add_back_raw(&ft_nm->symbol_list, (void*)node);
		if (ft_nm->is_64)
			sym64++;
		else
			sym32++;
		sym_index++;
	}
}

void	free_sys_node(void *content)
{
	free(content);
}

void	parse_elf_header(t_ft_nm *ft_nm)
{
	Elf64_Ehdr	*ehdr = (Elf64_Ehdr*)ft_nm->file_head;	

	scan_file_header(ft_nm, ehdr);
	
	if (ft_nm->status != NM_STATUS_0)
		return ;
	
	generate_symbol_list(ft_nm);

	/* put header */
	if (ft_nm->file_list_len >= 2)
		ft_printf("\n%s:\n", ft_nm->file_name);

	/* sort */
	ft_symbol_list_sort(ft_nm);
	ft_list_show(ft_nm->symbol_list, display_symbol_node_64);
	ft_list_clear(&ft_nm->symbol_list, free_sys_node);
}
