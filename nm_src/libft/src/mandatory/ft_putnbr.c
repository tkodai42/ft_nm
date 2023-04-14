#include "libft.h"

void	ft_putnbr(int num)
{
	char	buf[100 + 1];
	char	table[] = "0123456789";
	char	*head;
	int		sign = 1;

	head = buf + 100;
	*head = '\0';
	if (num < 0)
		sign = -1;
	while (*head == '\0' || num != 0)
	{
		*(--head) = table[num % 10 * sign];
		num /= 10;
	}
	if (sign == -1)
		*(--head) = '-';
	ft_putstr(head);
}
