#include "ft_nm.h"
#include "../includes/elf.h"


int		check_fh_magic_number_ELF(t_ft_nm *ft_nm, Elf64_Ehdr *ehdr_64)
{
	if (ehdr_64->e_ident[EI_MAG0] != 0x7F)
	{
		ft_nm->status = NM_HDR_ERROR;
		return 0;
	}
	
	return 1;
}

void	check_file_header(t_ft_nm *ft_nm, Elf64_Ehdr *ehdr_64)
{			
	if (is_valid_offset(ft_nm, ft_nm->file_head + sizeof(Elf64_Ehdr)) == 0)
		return ;

	/* check ELF */		
	if (check_fh_magic_number_ELF(ft_nm, ehdr_64) == 0)
		return ;

}

void	nm_solve(t_ft_nm *ft_nm)
{
	Elf64_Ehdr	*ehdr = (Elf64_Ehdr*)ft_nm->file_head;	

	check_file_header(ft_nm, ehdr);
	if (ft_nm->status != NM_STATUS_0)
		return ;
		
}
