#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdint.h>
#include "elf.h"
#include "../includes/elf.h"
#include "ft_nm.h"
#include <string.h>

void	error_exit(char *str)
{
	ft_putstr(str);
	exit(0);
}

int		open_file(int argc, char *argv[])
{
	int		fd;

	if (argc != 2)
		return -1;
	fd = open(argv[1], O_RDWR);
	return fd;
}


int		get_file_size(int fd)
{
	struct stat sb;

	fstat(fd, &sb);
	printf("FILE SIZE: %lld\n", sb.st_size);
	return sb.st_size;
}
/*
void	show_elf64_shdr(Elf64_Shdr *shdr)
{
	printf("\nSection header: %p\n", shdr);
	printf("sh_name: %%d: %d\n", shdr->sh_name);
	//printf("[name] %%s: %s\n", )
	printf("sh_flags: %%llu: %llu\n", shdr->sh_flags);
	printf("sh_addr: %%llu: %llu\n", shdr->sh_addr);

	(void)shdr;
}

void	show_elf64_shdrs(Elf64_Ehdr *ehdr)
{
	Elf64_Shdr *shdr;

	//for (int i = 0; i < ehdr->e_shnum; i++)
	int i = 2;
	{
		shdr = g_head + ehdr->e_shoff + (i * ehdr->e_shentsize);
		show_elf64_shdr(shdr);
	}
}
*/
void	show_elf64_header(Elf64_Ehdr *ehdr)
{
	printf("\nFile header: %p\n", ehdr);
	//e_ident[EI_MAG0]
	printf("e_ident[EI_MAG0]: %%x: %x\n", ehdr->e_ident[EI_MAG0]);
	printf("e_ident[EI_MAG1]: %%c: %c\n", ehdr->e_ident[EI_MAG1]);
	printf("e_ident[EI_MAG2]: %%c: %c\n", ehdr->e_ident[EI_MAG2]);
	printf("e_ident[EI_MAG3]: %%c: %c\n", ehdr->e_ident[EI_MAG3]);
	printf("e_ident[EI_VERSION]: %%d: %d\n", ehdr->e_ident[EI_VERSION]);

	printf("-- section --\n");
	printf("e_shoff: %%llu: %llu\n", ehdr->e_shoff);
	printf("e_shentsize: %%hu: %hu\n", ehdr->e_shentsize);
	printf("e_shnum: %%hu: %hu\n", ehdr->e_shnum);
	printf("e_shstrndx: %%hu: %hu\n", ehdr->e_shstrndx);

	printf("\n");
}


void	get_file_header(t_ft_nm *data)
{
	data->file_size = get_file_size(data->fd);
	data->head = mmap(NULL, data->file_size, PROT_READ, MAP_SHARED, data->fd, 0);

	printf("head: %p\n", data->head);

	Elf64_Ehdr* ehdr = (Elf64_Ehdr*)data->head;

	show_elf64_header(ehdr);
	//show_elf64_shdrs(ehdr);

	return ;

}

void	set_shstrndx_64(t_ft_nm *data)
{
	Elf64_Ehdr* ehdr = (Elf64_Ehdr*)data->head;
	Elf64_Shdr *shdr = data->head + ehdr->e_shoff +
						(ehdr->e_shstrndx * ehdr->e_shentsize);
	
	data->shstrndx = data->head + shdr->sh_offset;
	printf("%llu\n", shdr->sh_entsize);

	printf("%s\n", data->shstrndx);
	for (int i = 0; i < ehdr->e_shnum; i++)
	{
		shdr = data->head + ehdr->e_shoff + (ehdr->e_shentsize * i);
		printf("[%d] %s\n", i, data->shstrndx + shdr->sh_name);
	}
	
	//set symtab
	for (int i = 0; i < ehdr->e_shnum; i++)
	{
		shdr = data->head + ehdr->e_shoff + (ehdr->e_shentsize * i);
		//printf("set sym [%d]: %d\n", i, shdr->sh_type);
		if (shdr->sh_type == SHT_STRTAB)
			data->strtab_index = i;
		if (shdr->sh_type == SHT_SYMTAB)
			data->symtab_index = i;
	}
	//show symbol
	Elf64_Shdr *symbol_section = data->head + ehdr->e_shoff +
				(ehdr->e_shentsize * 27);
				//(ehdr->e_shentsize * data->symtab_index);
	Elf64_Shdr *strtab_section = data->head + ehdr->e_shoff +
				(ehdr->e_shentsize * 28);
				//(ehdr->e_shentsize * data->strtab_index);
	char *str_head = data->head + strtab_section->sh_offset;
	for (unsigned long long i = 0; i < strtab_section->sh_size; i++)
	{
		//symbol = data->head + symbol_sec->sh_offset + (sizeof(Elf64_Sym) * i);
		//printf("[%llu] \n", i);
		printf("%c", *(str_head + i));
		if (*(str_head + i) == 0)
			printf("\n");
	}

	Elf64_Sym  *symbol;
	int index = 0;
	for (unsigned long long i = 0; i < symbol_section->sh_size; i += sizeof(Elf64_Sym))
	{
		symbol = data->head + symbol_section->sh_offset + i;
		//printf("[%d] %d", index, symbol->st_name);
		if (symbol->st_name != 0)// && symbol->st_value != 0)
		{
			printf("%016llx ", symbol->st_value);
			printf("info:%d", symbol->st_info);
			printf("[%d %d]", ELF64_ST_BIND(symbol->st_info),
							ELF64_ST_TYPE(symbol->st_info));
			//printf("[%d]", ELF64_ST_VISIBILITY(symbol->st_other)),
			printf("[%d]", symbol->st_other),
			printf("[%s]", (str_head + symbol->st_name));
			printf(" st_shndx: %d", symbol->st_shndx);
			
			printf("\n");
		}
		index++;
	}

}

int		main(int argc, char *argv[])
{
	int			fd;
	t_ft_nm		data;

	fd = open_file(argc, argv);
	if (fd == -1)
		error_exit("Error: open\n");
	data.fd = fd;
	get_file_header(&data);
	set_shstrndx_64(&data);
	//get_symbol_table_
}
