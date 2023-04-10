#include "ft_nm.h"
#include "../includes/elf.h"

void	*get_sections_offset(t_ft_nm *ft_nm)
{
	if (ft_nm->is_64)
	{
		Elf64_Ehdr *ehdr_64	= (Elf64_Ehdr*)ft_nm->file_head;
		Elf64_Shdr *shdr_64 = ft_nm->file_head + ehdr_64->e_shoff; 
		return shdr_64;
	}
	else
	{
		Elf32_Ehdr *ehdr_32	= (Elf32_Ehdr*)ft_nm->file_head;
		Elf32_Shdr *shdr_32 = ft_nm->file_head + ehdr_32->e_shoff;
	
		return shdr_32;
	}
}

void	*get_section(t_ft_nm *ft_nm, int index)
{
	if (ft_nm->is_64)
	{
		Elf64_Ehdr *ehdr_64	= (Elf64_Ehdr*)ft_nm->file_head;
		Elf64_Shdr *shdr_64 = ft_nm->file_head + ehdr_64->e_shoff;
	
		shdr_64 += index;
		return shdr_64;
	}
	else
	{
		Elf32_Ehdr *ehdr_32	= (Elf32_Ehdr*)ft_nm->file_head;
		Elf32_Shdr *shdr_32 = ft_nm->file_head + ehdr_32->e_shoff;
	
		shdr_32 += index;
		return shdr_32;
	}
}

int		get_sections_size(t_ft_nm *ft_nm)
{
	if (ft_nm->is_64)
	{
		Elf64_Ehdr *ehdr_64	= (Elf64_Ehdr*)ft_nm->file_head;
	
		return ehdr_64->e_shnum;
	}
	else
	{
		Elf32_Ehdr *ehdr_32	= (Elf32_Ehdr*)ft_nm->file_head;
	
		return ehdr_32->e_shnum;
	}
}

void	*get_shstrndx_section(t_ft_nm *ft_nm)
{
	Elf64_Ehdr *ehdr_64	= (Elf64_Ehdr*)ft_nm->file_head;
	Elf64_Shdr *shdr_64 = ft_nm->file_head + ehdr_64->e_shoff;

	shdr_64 += ehdr_64->e_shstrndx;//need check
	return shdr_64;
}

const char	*get_section_name(t_ft_nm *ft_nm, void *shdr)
{
	Elf64_Shdr	*shdr_64 = shdr;
	Elf64_Shdr	*shdr_section_names = get_shstrndx_section(ft_nm);
	char		*section_name_ptr;

	section_name_ptr = ft_nm->file_head + shdr_section_names->sh_offset;
	section_name_ptr += shdr_64->sh_name;

	return section_name_ptr;
}
