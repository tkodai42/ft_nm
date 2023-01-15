#include "libft.h"

void	ft_puthex(int num, int digit, int big)
{
	char	buf[100 + 1];
	char	dump_b[] = "0123456789ABCDEF";
	char	dump_s[] = "0123456789abcdef";
	char	*dump = dump_b;
	char	*head;
	int		sign = 1;

	if (big == 0)
		dump = dump_s;
	head = buf + 100;
	*head = '\0';
	if (num < 0)
		sign = -1;
	while (*head == '\0' || num != 0)
	{
		*(--head) = dump[(num % 16 * sign)];
		num = num / 16;
	}
	
	// fill 0
	int		size = (buf + 100) - head;

	while (size < digit)
	{
		*(--head) = '0';
		size++;
	}
	ft_putstr(head);
}
