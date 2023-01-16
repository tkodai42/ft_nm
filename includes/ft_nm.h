#ifndef FT_NM
#define	FT_NM

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdint.h>
#include <string.h>

#include "./elf.h"
#include "elf.h"
#include "libft.h"

typedef struct	s_ft_nm
{
	void		*head;
	int			fd;
	long long	file_size;

	//option flag
	
	char		*shstrndx;
	int			strtab_index;
	int			symtab_index;

	//
	char		*prog_name_ptr;
	

}				t_ft_nm;

typedef struct	s_sh_node
{
	t_ft_nm				*nm_ptr;
	unsigned long long	sh_offset;
}				t_sh_node;

#endif
