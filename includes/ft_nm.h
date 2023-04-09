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
#include <errno.h>

#include "./elf.h"
#include "elf.h"
#include "libft.h"

#define DEBUG_PRINT printf("file: %s, func: %s (%d)\n", __FILE__, __func__, __LINE__);
#define DEFAULT_ARG_FILE "./parse_files/ELF/hello"

#define NM_STATUS_0					0
#define NM_MALLOC_ERROR 			1
#define NM_ARG_OPTION_ERROR			2

enum	option_enum
{
	OPTION_a,
	OPTION_g,
	OPTION_u,
	OPTION_r,
	OPTION_p
};

#define OPTION_BIT_a	(1 << OPTION_a)
#define OPTION_BIT_g	(1 << OPTION_g)
#define OPTION_BIT_u	(1 << OPTION_u)
#define OPTION_BIT_r	(1 << OPTION_r)
#define OPTION_BIT_p	(1 << OPTION_p)

typedef struct		s_option
{
	int		flag_bit;
	int		error;
	int		scan_bit;
}					t_option;

typedef struct		s_ft_nm
{
	int				argc;
	char			**argv;
	int				status;

	t_option		option;

	t_list_node		*file_list;

	int				file_size;
	void			*file_head;
}					t_ft_nm;

//read_option
void	read_option(t_ft_nm *ft_nm);

//execute_nm
void	execute_nm(t_ft_nm *ft_nm);

#endif
