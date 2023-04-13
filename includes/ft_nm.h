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
#include <limits.h>

#include "./elf.h"
#include "elf.h"
#include "libft.h"

#define DEBUG_PRINT printf("file: %s, func: %s (%d)\n", __FILE__, __func__, __LINE__);
#define DEFAULT_ARG_FILE "./parse_files/ELF/hello"

#define NM_STATUS_0					0
#define NM_MALLOC_ERROR 			1
#define NM_ARG_OPTION_ERROR			2
#define NM_MEM_SEGFALULT			3
#define NM_HDR_ERROR				4
#define NM_ERROR_MSG				5

#define NM_DEBUG 1
#define NM_OS_IS_LINUX				1

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

#define NM_OPTION_a(i)	(i & OPTION_BIT_a)
#define NM_OPTION_g(i)	(i & OPTION_BIT_g)
#define NM_OPTION_u(i)	(i & OPTION_BIT_u)
#define NM_OPTION_r(i)	(i & OPTION_BIT_r)
#define NM_OPTION_p(i)	(i & OPTION_BIT_p)

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
	const char		*status_msg;
	int				is_64;

	t_option		option;

	t_list_node		*file_list;

	int				file_size;
	char			*file_name;
	void			*file_head;
	void			*file_end;

	/* symbol list */
	t_list_node		*symbol_list;

}					t_ft_nm;

typedef struct		s_sym_node64
{
	t_ft_nm		*ft_nm;
	Elf64_Sym	*sym;
	Elf64_Shdr	*shdr;
	const char	*sym_name_ptr;
	const char	*shdr_name_ptr;
}					t_sym_node64;

//read_option
void	read_option(t_ft_nm *ft_nm);

//execute_nm
void	execute_nm(t_ft_nm *ft_nm);

//solve
void	nm_solve(t_ft_nm *ft_nm);

//error
void	put_file_error(const char *f);
void	set_end_offset(t_ft_nm *ft_nm);
void	put_nm_error(t_ft_nm *ft_nm);
int		is_valid_offset(t_ft_nm *f, void *ptr);
void	set_end_offset(t_ft_nm *ft);

//section
void	*get_sections_offset(t_ft_nm *ft_nm);
void	*get_section_by_index(t_ft_nm *ft_nm, int index);
int		get_sections_size(t_ft_nm *ft_nm);
const char	*get_section_name(t_ft_nm *ft_nm, void *shdr);
void	*get_section_by_type(t_ft_nm *ft_nm, unsigned int type);
void	*get_section_by_name(t_ft_nm *ft_nm, const char *type);
void	*get_section_by_sym(t_ft_nm *ft_nm, void *sym);
//symbol
const char	*get_symbol_name(t_ft_nm *ft_nm, void *sym);

void	display_symbol_node_64(void *content);

#endif
