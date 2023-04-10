#include "ft_nm.h"
#include "../includes/elf.h"

void	*get_sections_offset(t_ft_nm *ft_nm)
{
	Elf64_Ehdr *ehdr_64	= (Elf64_Ehdr*)ft_nm->file_head;
	Elf64_Shdr *shdr_64 = ft_nm->file_head + ehdr_64->e_shoff;
	
	return shdr_64;
}

void	*get_section(t_ft_nm *ft_nm, int index)
{
	Elf64_Ehdr *ehdr_64	= (Elf64_Ehdr*)ft_nm->file_head;
	Elf64_Shdr *shdr_64 = ft_nm->file_head + ehdr_64->e_shoff;
	
	shdr_64 += index;
	return shdr_64;
}

int		get_sections_size(t_ft_nm *ft_nm)
{
	Elf64_Ehdr *ehdr_64	= (Elf64_Ehdr*)ft_nm->file_head;
	
	return ehdr_64->e_shnum;
}


