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

typedef struct	s_elf_64
{
	void		*head;
	Elf64_Ehdr	*ehdr;		//ELF header
	Elf64_Shdr	*shdr_head;	//section header head ptr
	Elf64_Shdr	*shdr_header_table;

	Elf64_Shdr	*shdr_symbol;
	Elf64_Shdr	*shdr_strtab;
	Elf64_Sym	*sym_head;

	char		*sh_name_tab_ptr;  //section header name table head ptr
	char		*sym_name_tab_ptr; //symbol name table head ptr

}				t_elf_64;

typedef struct	s_ft_nm
{
	//option
	t_option	option;


	int			status;
	void		*head;

	//type?
	int			machine_type;
	int			elf_format_size; //1 or 2 to signify 32- or 64-bit format

	//read file
	char		*file_name;
	int			file_size;

	
	//
	t_list_node	*file_list;

	//symbol
	t_list_node	*symbol_list;

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

typedef struct	s_sh_node_64
{
	t_ft_nm				*nm_ptr;
	t_elf_64			*d;
	Elf64_Sym			*symbol;
	//unsigned long long	sh_offset;
}				t_sh_node_64;


void	read_option(t_ft_nm *n, int ar, char **argv);
void	open_file(t_ft_nm *n);
void	execute(t_ft_nm *n);
void	nm_solve(t_ft_nm *n);
int		is_valid_address(t_ft_nm *ft_nm, void *ptr);

//scan 64
void	scan_elf_header_64(t_ft_nm *ft_nm, t_elf_64 *ehdr);
void	scan_section_header_64(t_ft_nm *f, t_elf_64 *e);

//symbol
void	display_symbol_node_64(void *content);
int		sort_symbol_node_64(void *c1, void *c2);

//error
void	put_nm_error(char *f, char *m);
#endif
