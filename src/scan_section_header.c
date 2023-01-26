#include "../includes/ft_nm.h"
#include "../includes/elf.h"


void	show_section_name(t_elf_64 *d)
{
	Elf64_Shdr	*shdr;

	shdr = d->shdr_head;
	char	*str = (char *)(d->head + d->shdr_header_table->sh_offset);
	for (int i = 0; i < d->ehdr->e_shnum; i++)
	{
		printf("[%d] %s\n", i, str + shdr->sh_name);
		shdr++;
	}
}

void	show_symbol_name(t_elf_64 *d)
{
	Elf64_Sym	*symbol;
	char		*str = d->sym_name_tab_ptr;

	symbol = d->sym_head;
	for (unsigned long long i = 0; i * sizeof(Elf64_Sym) < d->shdr_symbol->sh_size; i++)
	{
		printf("[%llu] %s\n", i, str + symbol->st_name);

		symbol++;
	}

}

int		check_all_section_offset(t_ft_nm *ft_nm, t_elf_64 *d)
{
	Elf64_Shdr	*shdr;
	void		*offset_pos;

	shdr = d->shdr_head;

	for (int i = 0; i < d->ehdr->e_shnum; i++)
	{
		//printf("%llu\n", shdr->sh_offset);
		offset_pos = d->head + shdr->sh_offset;
		if (is_valid_address(ft_nm, offset_pos) != 0)
			return 1;
		shdr++;
	}
	return 0;
}

void	set_symbol_section(t_ft_nm *ft_nm, t_elf_64 *d)
{
	Elf64_Shdr	*shdr;

	shdr = d->shdr_head;

	for (int i = 0; i < d->ehdr->e_shnum; i++)
	{
		//check sh_name offset
		if (strcmp(d->sh_name_tab_ptr + shdr->sh_name, ".symtab") == 0)
		{
			d->shdr_symbol = shdr;
			d->sym_head = d->head + shdr->sh_offset;
		}
		if (strcmp(d->sh_name_tab_ptr + shdr->sh_name, ".strtab") == 0)
			d->shdr_strtab = shdr;
		shdr++;
	}
	(void)ft_nm;
}

void	scan_section_header_64(t_ft_nm *ft_nm, t_elf_64 *elf_data)
{
	show_section_name(elf_data); //for debug

	//check offsets
	if (check_all_section_offset(ft_nm, elf_data) != 0)
	{
		printf("Error: section has invalid offset\n");
		return ;
	}
	//set section name
	elf_data->sh_name_tab_ptr = (char*)elf_data->head + elf_data->shdr_header_table->sh_offset;

	//check duplicate

	//set symbol str table and symbol table
	set_symbol_section(ft_nm, elf_data);

	//set symbol str head
	elf_data->sym_name_tab_ptr = (char*)elf_data->head + elf_data->shdr_strtab->sh_offset;
	
	show_symbol_name(elf_data); //for debug;

	(void)ft_nm;
	(void)elf_data;
}
