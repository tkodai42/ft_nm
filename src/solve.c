#include "../includes/ft_nm.h"
#include "../includes/elf.h"



void	set_architecture_32_or_64(t_ft_nm *ft_nm, Elf64_Ehdr *tmp_ehdr)
{
	ft_nm->status = is_valid_address(ft_nm, &(tmp_ehdr->e_ident[EI_CLASS]));
	if (ft_nm->status != 0)
		return ; //put error?
	
	ft_nm->elf_format_size = tmp_ehdr->e_ident[EI_CLASS];//1 or 2 32 or 64
}

void	nm_solve(t_ft_nm *ft_nm)
{
	Elf64_Ehdr*	tmp_ehdr = (Elf64_Ehdr*)ft_nm->head;
	t_elf_64	elf_data_64;
	//Elf32_Ehdr* tmp_ehdr32;

	set_architecture_32_or_64(ft_nm, tmp_ehdr);
	if (ft_nm->status != 0)
		return ;

	elf_data_64.ehdr = (Elf64_Ehdr*)ft_nm->head;
	elf_data_64.head = ft_nm->head;

	if (ft_nm->elf_format_size == 2) //mean 64
	{
		elf_data_64.ehdr = (Elf64_Ehdr*)ft_nm->head;
		scan_elf_header_64(ft_nm, &elf_data_64);
	}
	else //32
	{
		printf(">>> 32 <<<\n");	
		scan_elf_header_64(ft_nm, &elf_data_64);
	}

}
