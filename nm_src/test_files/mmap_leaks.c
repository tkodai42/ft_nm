#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h> 


int		f(int argc, char **argv)
{
	int			fd;
	const char 	*file_name;

	// OPEN
	if (argc != 2)
		file_name = "mmap_leaks.c";
	else
		file_name = argv[1];

	fd = open(file_name, O_RDONLY);

	if (fd == -1)
		return printf("Error: open: fd\n");

	
	//STAT
	struct stat	st;
	int			ret;

	ret	= fstat(fd, &st);
	if (ret == -1)
		return printf("Error: fstat: \n");

	printf("fileName: %s size: %lld\n", file_name, st.st_size);


	void	*raw = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

	if (raw == NULL)
		return printf("Error: mmap: \n");
		
	munmap(raw, st.st_size);
	//write(1, (char*)raw, st.st_size);

	return 0;
}

int		main(int argc, char *argv[])
{
	f(argc, argv);
	system("leaks a.out");
}
