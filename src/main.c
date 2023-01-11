#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE	10000
char	file_path[] = "./elf";
char	buf[BUFFER_SIZE + 1];

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
}
