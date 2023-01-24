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

#define	NM_STATUS_0				0
#define NM_STATUS_MALLOC_ERROR	1

enum option_enum {
  OPTION_a,
  OPTION_g,
  OPTION_u,
  OPTION_r,
  OPTION_p
};

#define OPTION_BIT_a			(1 << OPTION_a)
#define OPTION_BIT_g			(1 << OPTION_g)
#define OPTION_BIT_u			(1 << OPTION_u)
#define OPTION_BIT_r			(1 << OPTION_r)
#define OPTION_BIT_p			(1 << OPTION_p)

typedef struct	s_option
{
	int		option_bit;
	int		option_error;
	int		scan_bit;

}				t_option;


typedef struct	s_ft_nm
{
	int			status;
	void		*head;

	//read file
	int			fd;
	char		*file_name;
	
	//
	t_list_node	*file_list;

	/*
	void		*head;
	int			fd;
	long long	file_size;

	//option flag
	
	char		*shstrndx;
	int			strtab_index;
	int			symtab_index;

	//
	char		*prog_name_ptr;
		*/

}				t_ft_nm;

typedef struct	s_sh_node
{
	t_ft_nm				*nm_ptr;
	unsigned long long	sh_offset;
}				t_sh_node;


void	read_option(t_ft_nm *n, int ar, char **argv);

#endif
