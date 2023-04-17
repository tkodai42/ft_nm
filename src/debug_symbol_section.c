#include "ft_nm.h"
#include "../includes/elf.h"

void	debug_print_symbol_bind(int bind)
{
	//ft_putstr(" [");
	if (STB_LOCAL == bind)
		ft_printf(" %10s |", "STB_LOCAL");
	else if (STB_GLOBAL == bind)
		ft_printf(" %10s |", "STB_GLOBAL");
	else if (STB_WEAK == bind)
		ft_printf(" %10s |", "STB_WEAK");
	else if (STB_LOOS == bind)
		ft_printf(" %10s |", "STB_LOOS");
	else if (STB_HIOS == bind)
		ft_printf(" %10s |", "STB_HIOS");
	else if (STB_LOPROC == bind)
		ft_printf(" %10s |", "STB_LOPROC");
	else if (STB_HIPROC == bind)
		ft_printf(" %10s |", "STB_HIPROC");
	else
		ft_printf(" %10s |", "");
	
	//ft_putstr("] ");
}

void	debug_print_symbol_type(int type)
{
	//ft_putstr(" [");
	if (STT_NOTYPE == type)
		ft_printf("%12s |", "STT_NOTYPE");
	else if (STT_OBJECT == type)
		ft_printf("%12s |", "STT_OBJECT");
	else if (STT_FUNC == type)
		ft_printf("%12s |", "STT_FUNC");
	else if (STT_SECTION == type)
		ft_printf("%12s |", "STT_SECTION");
	else if (STT_FILE == type)
		ft_printf("%12s |", "STT_FILE");
	else if (STT_COMMON == type)
		ft_printf("%12s |", "STT_COMMON");
	else if (STT_TLS == type)
		ft_printf("%12s |", "STT_TLS");
	else if (STT_LOOS == type)
		ft_printf("%12s |", "STT_LOOS");
	else if (STT_HIOS == type)
		ft_printf("%12s |", "STT_HIOS");
	else if (STT_LOPROC == type)
		ft_printf("%12s |", "STT_LOPROC");
	else if (STT_SPARC_REGISTER == type)
		ft_printf("%12s |", "STT_SPARC_REGISTER");
	else if (STT_HIPROC == type)
		ft_printf("%12s |", "STT_HIPROC");
	else
		ft_printf("%12s |", "");
	
	//ft_putstr("] ");
}

void	debug_print_section_type(int type)
{
	if (SHT_NULL == type)
		ft_printf("%14s |", "SHT_NULL");
	else if (SHT_PROGBITS == type)
		ft_printf("%14s |", "SHT_PROGBITS");
	else if (SHT_SYMTAB == type)
		ft_printf("%14s |", "SHT_SYMTAB");
	else if (SHT_STRTAB == type)
		ft_printf("%14s |", "SHT_STRTAB");
	else if (SHT_RELA == type)
		ft_printf("%14s |", "SHT_RELA");
	else if (SHT_HASH == type)
		ft_printf("%14s |", "SHT_HASH");
	else if (SHT_DYNAMIC == type)
		ft_printf("%14s |", "SHT_DYNAMIC");
	else if (SHT_NOTE == type)
		ft_printf("%14s |", "SHT_NOTE");
	else if (SHT_NOBITS == type)
		ft_printf("%14s |", "SHT_NOBITS");
	else if (SHT_REL == type)
		ft_printf("%14s |", "SHT_REL");
	else if (SHT_SHLIB == type)
		ft_printf("%14s |", "SHT_SHLIB");
	else if (SHT_DYNSYM == type)
		ft_printf("%14s |", "SHT_DYNSYM");
	else if (SHT_INIT_ARRAY == type)
		ft_printf("%14s |", "SHT_INIT_ARRAY");
	else if (SHT_FINI_ARRAY == type)
		ft_printf("%14s |", "SHT_FINI_ARRAY");
	else if (SHT_PREINIT_ARRAY == type)
		ft_printf("%14s |", "SHT_PREINIT_ARRAY");
	else if (SHT_GROUP == type)
		ft_printf("%14s |", "SHT_GROUP");
	else if (SHT_SYMTAB_SHNDX == type)
		ft_printf("%14s |", "SHT_SYMTAB_SHNDX");
	else if (SHT_NUM == type)
		ft_printf("%14s |", "SHT_NUM");
	else if (SHT_LOOS == type)
		ft_printf("%14s |", "SHT_LOOS");
	else if (SHN_ABS == type)
		ft_printf("%14s |", "(SHN_ABS)");
	else
		ft_printf("%14s |", "");
			
}

void	debug_print_section_flags(unsigned int flag)
{
	int		wrote_len = 0;

	wrote_len = ft_printf(" ");
	if (SHF_WRITE & flag)
		wrote_len += ft_printf("%s ", "SHF_WRITE");
	if (SHF_ALLOC & flag)
		wrote_len += ft_printf("%s ", "SHF_ALLOC");
	if (SHF_EXECINSTR & flag)
		wrote_len += ft_printf("%s ", "SHF_EXECINSTR");
	if (SHF_MERGE & flag) 
		wrote_len += ft_printf("%s ", "SHF_MERGE");
	if (SHF_STRINGS & flag)
		wrote_len += ft_printf("%s ", "SHF_STRINGS");
	if (SHF_INFO_LINK & flag)
		wrote_len += ft_printf("%s ", "SHF_INFO_LINK");
	if (SHF_LINK_ORDER & flag)
		wrote_len += ft_printf("%s ", "SHF_LINK_ORDER");
	if (SHF_OS_NONCONFORMING & flag)
		wrote_len += ft_printf("%s ", "SHF_OS_NONCONFORMING");
	if (SHF_GROUP & flag)
		wrote_len += ft_printf("%s ", "SHF_GROUP");
	if (SHF_TLS & flag)
		wrote_len += ft_printf("%s ", "SHF_TLS");
	if (SHF_MASKOS & flag)
		wrote_len += ft_printf("%s ", "SHF_MASKOS");
	if (SHF_MASKPROC & flag)
		wrote_len += ft_printf("%s ", "SHF_MASKPROC");
	if (SHF_ORDERED & flag)
		wrote_len += ft_printf("%s ", "SHF_ORDERED");
	if (SHF_EXCLUDE & flag)
		wrote_len += ft_printf("%s ", "SHF_EXCLUDE");
	while (wrote_len < 25)
		wrote_len += ft_printf(" ");
	ft_printf("|");
}

