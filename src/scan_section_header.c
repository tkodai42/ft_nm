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

void	scan_section_header_64(t_ft_nm *ft_nm, t_elf_64 *elf_data)
{
	show_section_name(elf_data); //for debug



	(void)ft_nm;
	(void)elf_data;
}
