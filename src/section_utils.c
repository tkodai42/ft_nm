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

void	*get_section_by_index(t_ft_nm *ft_nm, int index)
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
	if (ft_nm->is_64)
	{
		Elf64_Ehdr *ehdr_64	= (Elf64_Ehdr*)ft_nm->file_head;
		Elf64_Shdr *shdr_64 = ft_nm->file_head + ehdr_64->e_shoff;

		shdr_64 += ehdr_64->e_shstrndx;//need check
		return shdr_64;
	}
	else
	{
		Elf32_Ehdr *ehdr_32	= (Elf32_Ehdr*)ft_nm->file_head;
		Elf32_Shdr *shdr_32 = ft_nm->file_head + ehdr_32->e_shoff;

		shdr_32 += ehdr_32->e_shstrndx;//need check
		return shdr_32;
	}
}

void	*get_section_by_type(t_ft_nm *ft_nm, unsigned int type)
{
	if (ft_nm->is_64)
	{
		Elf64_Shdr	*shdr_64 = get_sections_offset(ft_nm);
		int			section_size = get_sections_size(ft_nm);
		int			section_index = 0;

		//check all section
		while (section_index < section_size)
		{
			if (is_valid_offset(ft_nm, shdr_64) == 0)	
				return NULL;
			if (shdr_64->sh_type == type)
				return shdr_64;
			shdr_64++;
			section_index++;
		}
	}
	else
	{
		Elf32_Shdr	*shdr_32 = get_sections_offset(ft_nm);
		int			section_size = get_sections_size(ft_nm);
		int			section_index = 0;

		//check all section
		while (section_index < section_size)
		{
			if (is_valid_offset(ft_nm, shdr_32) == 0)	
				return NULL;
			if (shdr_32->sh_type == type)
				return shdr_32;
			shdr_32++;
			section_index++;
		}
	}
	return NULL;
}

const char	*get_section_name(t_ft_nm *ft_nm, void *shdr)
{
	if (ft_nm->is_64)
	{
		Elf64_Shdr	*shdr_64 = shdr;
		Elf64_Shdr	*shdr_section_names = get_shstrndx_section(ft_nm);
		char		*section_name_ptr;

		if (shdr == NULL || shdr_64->sh_name == 0)
			return "";
		section_name_ptr = ft_nm->file_head + shdr_section_names->sh_offset;
		section_name_ptr += shdr_64->sh_name;

		return section_name_ptr;
	}
	else
	{
		Elf32_Shdr	*shdr_32 = shdr;
		Elf32_Shdr	*shdr_section_names = get_shstrndx_section(ft_nm);
		char		*section_name_ptr;

		if (shdr == NULL || shdr_32->sh_name == 0)
			return "";
		section_name_ptr = ft_nm->file_head + shdr_section_names->sh_offset;
		section_name_ptr += shdr_32->sh_name;

		return section_name_ptr;
	}
}

void	*get_section_by_name(t_ft_nm *ft_nm, const char *name)
{
	if (ft_nm->is_64)
	{
		Elf64_Shdr	*shdr_64 = get_sections_offset(ft_nm);
		int			section_size = get_sections_size(ft_nm);
		int			section_index = 0;
		const char *sect_name;

		while (section_index < section_size)
		{
			if (is_valid_offset(ft_nm, shdr_64) == 0)	
				return NULL;
			sect_name = get_section_name(ft_nm, shdr_64);
			if (ft_strcmp(sect_name, name) == 0)
				return shdr_64;
			shdr_64++;
			section_index++;
		}
	}
	else
	{
		Elf32_Shdr	*shdr_32 = get_sections_offset(ft_nm);
		int			section_size = get_sections_size(ft_nm);
		int			section_index = 0;
		const char *sect_name;

		while (section_index < section_size)
		{
			if (is_valid_offset(ft_nm, shdr_32) == 0)	
				return NULL;
			sect_name = get_section_name(ft_nm, shdr_32);
			if (ft_strcmp(sect_name, name) == 0)
				return shdr_32;
			shdr_32++;
			section_index++;
		}
	}
	return NULL;
}

const char *get_symbol_name(t_ft_nm *ft_nm, void *sym)
{
	if (ft_nm->is_64)
	{
		Elf64_Shdr	*symstr_section;

		symstr_section = get_section_by_name(ft_nm, ".strtab");
		if (((Elf64_Sym *)sym)->st_name == 0)
			return NULL;
		return ft_nm->file_head + symstr_section->sh_offset + ((Elf64_Sym *)sym)->st_name;
	}
	else
	{
		Elf32_Shdr	*symstr_section;

		symstr_section = get_section_by_name(ft_nm, ".strtab");
		if (((Elf32_Sym *)sym)->st_name == 0)
			return NULL;
		return ft_nm->file_head + symstr_section->sh_offset + ((Elf32_Sym *)sym)->st_name;
	}
}

void	*get_section_by_sym(t_ft_nm *ft_nm, void *sym_tmp)
{
	if (ft_nm->is_64)
	{
		Elf64_Sym	*sym = sym_tmp;
		int 		section_index = sym->st_shndx;
		Elf64_Shdr	*section_shdr;

		//if (section_index == SHN_UNDEF || section_index == SHN_ABS)
		if (section_index == SHN_ABS)
			return NULL;
		else
			return section_shdr = get_section_by_index(ft_nm, section_index);
	}
	else
	{
		Elf32_Sym	*sym = sym_tmp;
		int 		section_index = sym->st_shndx;
		Elf32_Shdr	*section_shdr;

		//if (section_index == SHN_UNDEF || section_index == SHN_ABS)
		if (section_index == SHN_ABS)
			return NULL;
		else
			return section_shdr = get_section_by_index(ft_nm, section_index);
	}
}
