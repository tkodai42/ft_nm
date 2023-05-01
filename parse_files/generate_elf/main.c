#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "../../includes/elf.h"

int		g_file_size;

void	alter(void *data)
{
	Elf64_Ehdr	*ehdr = data;

	ehdr->e_ident[EI_MAG0] = ELFMAG0;

//  Elf64_Half	e_type;			/* Object file type */
//  Elf64_Half	e_machine;		/* Architecture */
//  Elf64_Word	e_version;		/* Object file version */
//  Elf64_Addr	e_entry;		/* Entry point virtual address */
//  Elf64_Off	e_phoff;		/* Program header table file offset */
//  Elf64_Off	e_shoff;		/* Section header table file offset */
//  Elf64_Word	e_flags;		/* Processor-specific flags */
//  Elf64_Half	e_ehsize;		/* ELF header size in bytes */
//  Elf64_Half	e_phentsize;		/* Program header table entry size */
//  Elf64_Half	e_phnum;		/* Program header table entry count */
//  Elf64_Half	e_shentsize;		/* Section header table entry size */
//  Elf64_Half	e_shnum;		/* Section header table entry count */
//  Elf64_Half	e_shstrndx;		/* Section header string table index */

}

void	*map_file(const char *file_path)
{
	struct stat	st;
	int			fd;
	int			size;
	void		*data;

	//open
	if ((fd = open(file_path, O_RDWR)) == 1)
	{
		dprintf(STDERR_FILENO, "Error: open:\n");
		return NULL;
	}
	//fstat
	if (fstat(fd, &st) == -1)
	{
		close(fd);
		dprintf(STDERR_FILENO, "Error: fstat:\n");
		return NULL;
	}
	size = st.st_size;
	g_file_size = size;
	//mmap
	if ((data = mmap(NULL, size, PROT_WRITE, MAP_SHARED, fd, 0)) == NULL)
		dprintf(STDERR_FILENO, "Error: mmap:\n");
	close(fd);
	return data;
}

void	gen_file(void *data)
{
	unsigned char	*ptr = data;
	int				fd;

	fd = open("new_elf", O_RDWR | O_CREAT, 0777);

	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: open:\n");
		return ;
	}
	write(fd, ptr, g_file_size);
	close(fd);
}

int		main(int argc, char *argv[])
{
	void		*data;
	Elf64_Ehdr	my_ehd;

	if (argc != 2)
		return dprintf(STDERR_FILENO, "Error: invalid args\n");

	printf(">> INPUT FILE [%s]\n", argv[1]);
	/* mmap */
	data = map_file(argv[1]);

	alter(data);

	gen_file(data);
	munmap(data, g_file_size);
}
