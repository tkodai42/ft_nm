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
	Elf64_Shdr	*shdr_64 = get_sections_offset(ft_nm);
	int			section_size = get_sections_size(ft_nm);
	int			section_index = 0;

	if (section_size < 0)
	{
		ft_nm->status_msg = "SECTION NUM IS INVALID";
		ft_nm->status = NM_ERROR_MSG;
		return 0;
	}
	//check all section
	while (section_index < section_size)
	{
		if (is_valid_offset(ft_nm, shdr_64) == 0)	
			return 0;
		//TODO
		//セクションのオフセットの位置が有効？
		//セクションのオフセットからimage sizeが有効？
		shdr_64++;
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

	/* scan */
	/* scan */
	/* scan */
	/* scan */
	/* scan 32 or 64 */
	if (set_bit_format(ft_nm, ehdr_64) == 0)
		return ;

	/* check */
	if (check_section_offset(ft_nm) == 0)
		return ;
}

void	nm_solve(t_ft_nm *ft_nm)
{
	Elf64_Ehdr	*ehdr = (Elf64_Ehdr*)ft_nm->file_head;	

	scan_file_header(ft_nm, ehdr);
	if (ft_nm->status != NM_STATUS_0)
		return ;


}
