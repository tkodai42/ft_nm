#include "ft_nm.h"

void	put_help()
{
	ft_printf("Usage: ft_nm [option(s)] [file(s)]\n");
	ft_printf(" List symbols in [file(s)] (a.out by default).\n");
	ft_printf(" The options are:\n");
	ft_printf("  -a, --debug-syms       Display debugger-only symbols\n");
	ft_printf("  -g, --extern-only      Display only external symbols\n");
	ft_printf("  -p, --no-sort          Do not sort the symbols\n");
	ft_printf("  -r, --reverse-sort     Reverse the sense of the sort\n");
	ft_printf("  -u, --undefined-only   Display only undefined symbols\n");
	ft_printf("  -h, --help             Display this information\n");
	ft_printf("\n");
	ft_printf("ft_nm: supported targets: elf64-x86-64 elf32-x86-64\n");
}
