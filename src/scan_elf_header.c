#include "../includes/ft_nm.h"
#include "../includes/elf.h"

int		check_magic_number_ELF(Elf64_Ehdr *ehdr)
{
	printf("> check_ELF ");
	printf("[%x]", ehdr->e_ident[EI_MAG0]);
	printf("[%c]", ehdr->e_ident[EI_MAG1]);
	printf("[%c]", ehdr->e_ident[EI_MAG2]);
	printf("[%c]\n", ehdr->e_ident[EI_MAG3]);
	if (ehdr->e_ident[EI_MAG0] != 0x7F)
		return 1;
	if (ft_strncmp("ELF", (char *)&(ehdr->e_ident[EI_MAG1]), 3) != 0)
		return 1;
	return 0;
}

int		set_section_header(t_ft_nm *ft_nm, t_elf_64 *d)
{
	// === check simple offset check ===
	if (d->ehdr->e_shstrndx < 0)
	{
		printf("Error: e_shstrndx is negative\n");
		return 1;
	}
	if (d->ehdr->e_shnum < 0)
	{
		printf("Error: e_shnum is negative\n");
		return 1;
	}
	if (d->ehdr->e_shstrndx >= d->ehdr->e_shnum)
	{
		printf("Error: e_shstrndx index is invalid\n");
		return 1;
	}
	//check all section end
	ft_nm->status = is_valid_address(ft_nm, ft_nm->head + d->ehdr->e_shoff +
			(sizeof(Elf64_Shdr) * (d->ehdr->e_shnum)/* decrease 1 byte */));
	if (ft_nm->status != 0)
	{
		put_nm_error(ft_nm->file_name, "section table goes past the end of file");
		return 1;
	}

	//set section header head
	d->shdr_head = ft_nm->head + d->ehdr->e_shoff; 
	//set section header table
	d->shdr_header_table = d->shdr_head + d->ehdr->e_shstrndx;
	return 0;
}

void	scan_elf_header_64(t_ft_nm *ft_nm, t_elf_64 *elf_data)
{
	printf(">> scan_elf_header_64\n");
	//check header size
	ft_nm->status = is_valid_address(ft_nm, ft_nm->head + sizeof(Elf64_Ehdr));
	if (ft_nm->status != 0)
		return ;

	if ((ft_nm->status = check_magic_number_ELF(elf_data->ehdr)) != 0)
	{
		printf("Error: is this a elf file?\n");
		return ;
	}
	
	if (set_section_header(ft_nm, elf_data) != 0)
		return ;
	scan_section_header_64(ft_nm, elf_data);
}
