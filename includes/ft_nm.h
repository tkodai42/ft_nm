#ifndef FT_NM
#define	FT_NM

#include "./elf.h"
#include "elf.h"

typedef struct	s_ft_nm
{
	void		*head;
	int			fd;
	long long	file_size;

	//option flag
	
	char		*shstrndx;

}				t_ft_nm;

#endif
