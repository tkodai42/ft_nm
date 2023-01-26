#include "../includes/ft_nm.h"
#include "../includes/elf.h"

void	put_nm_error(char *file_name, char *message)
{
	ft_putstr(ES_WORD_RED);
	ft_putstr(ES_BOLD);
	ft_putstr("error: ");
	ft_putstr(ES_RESET);
	ft_putstr(file_name);
	ft_putstr(" ");
	ft_putstr(message);
	ft_putstr("\n\n");
}


