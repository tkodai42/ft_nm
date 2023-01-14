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

char	file_path[] = "./elf";
char	*g_strtab;

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


void	get_file_header(int fd)
{
	long long	_file_size = get_file_size(fd);
	void		*head = mmap(NULL, _file_size, PROT_READ, MAP_SHARED, fd, 0);
	g_head = head;

	printf("head: %p\n", head);

	Elf64_Ehdr* ehdr = (Elf64_Ehdr*)head;

	show_elf64_header(ehdr);
	show_elf64_shdrs(ehdr);

	return ;
	printf("e_phoff: %llx\n", ehdr->e_phoff);
	printf("e_phnum: %d\n", ehdr->e_phnum);

	Elf64_Phdr *phd = head + ehdr->e_phoff;

	printf("phd: %p\n", phd);

	// LOADセグメントの内容だけ表示する
	// readelfの結果と同じになる
	for (int i = 0; i < ehdr->e_phnum; i++) {
		if (phd[i].p_type == PT_LOAD) {
			printf("%d: %llx, %llx, %llx, %llx, %llx, %llx, %llx\n",
					i,
					(uint64_t)phd[i].p_offset,
					(uint64_t)phd[i].p_vaddr,
					(uint64_t)phd[i].p_paddr,
					(uint64_t)phd[i].p_filesz,
					(uint64_t)phd[i].p_memsz,
					(uint64_t)phd[i].p_flags,
					(uint64_t)phd[i].p_align);
		}
	}

	Elf64_Shdr* shder = head + ehdr->e_shoff;

	char *name = (char*)head + shder->sh_name;

	ft_putstr(name);
}

int		main(int argc, char *argv[])
{
	int		fd;

	fd = open_file(argc, argv);
	if (fd == -1)
		error_exit("Error: open\n");
	get_file_header(fd);
}

/*
int		main(int argc, char *argv[])
{
	int		fd;

	if (argc != 2)
		fd = open(file_path, O_RDWR);
	else
		fd = open(argv[1], O_RDWR);

	int		ret = read(fd, buf, BUFFER_SIZE);

	buf[ret] = '0';

	for (int i = 0; i < 200; i++)
	{
		if (i % 8 == 0)
			printf("%d: ", i * 8);
		printf("[%x]", buf[i]);
		if (i % 8 == 7)
			printf("\n");
	}

	printf("\n");

	for (int i = 0; i < 200; i++)
	{
		if (i % 8 == 0)
			printf("%d: ", i * 8);
		printf("[%d]", buf[i]);
		if (i % 8 == 7)
			printf("\n");
	}

	printf("\n");

	for (int i = 0; i < 200; i++)
	{
		if (i % 8 == 0)
			printf("%d: ", i * 8);
		printf("[%c]", buf[i]);
		if (i % 8 == 7)
			printf("\n");
	}

	//int		size = 0;

	close(fd);
	if (argc != 2)
		fd = open(file_path, O_RDWR);
	else
		fd = open(argv[1], O_RDWR);
 
	char str[] = "12345";

	printf("%d\n", ft_strlen(str));
}
*/
