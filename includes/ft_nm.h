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
#define DEFAULT_ARG_FILE "./parse_file/ELF/hello"

#define NM_STATUS_0		0
#define NM_MALLOC_ERROR 1

typedef struct		s_option
{
	int		flag_bit;
	int		error;
	int		scan_bit;
}					t_option;

typedef struct		s_ft_nm
{
	int		argc;
	char	**argv;
	int		status;

	t_option		option;
}					t_ft_nm;

//read_option
void	read_option(t_ft_nm *ft_nm);

#endif
