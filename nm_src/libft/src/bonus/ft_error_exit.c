#include "libft.h"

void	ft_put_error_msg_exit(const char *msg)
{
	ft_putstr_fd(ES_WORD_RED, 2);
	ft_putstr_fd(ES_BOLD, 2);
	ft_putstr_fd("error: ", 2);
	ft_putstr_fd(ES_RESET, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(0);
}

void	ft_error_exit(int flag)
{
	(void)flag;
	exit(0);
}
