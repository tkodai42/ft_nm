#include "ft_nm.h"
#include "../includes/elf.h"

int		check_fh_magic_number_ELF(t_ft_nm *ft_nm, Elf64_Ehdr *ehdr_64)
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

void	check_file_header(t_ft_nm *ft_nm, Elf64_Ehdr *ehdr_64)
{			
	if (is_valid_offset(ft_nm, ft_nm->file_head + sizeof(Elf64_Ehdr)) == 0)
		return ;

	/* check 0x7F E L F */		
	if (check_fh_magic_number_ELF(ft_nm, ehdr_64) == 0)
		return ;

	/* check */
	/* check */
	/* check */
	/* check */
	/* check 32 or 64 */
	if (set_bit_format(ft_nm, ehdr_64) == 0)
		return ;
}

void	nm_solve(t_ft_nm *ft_nm)
{
	Elf64_Ehdr	*ehdr = (Elf64_Ehdr*)ft_nm->file_head;	

	check_file_header(ft_nm, ehdr);
	if (ft_nm->status != NM_STATUS_0)
		return ;

}
