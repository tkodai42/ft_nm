#include "libft.h"

int		ft_setnbr(int num, char *set_buf)
{
	char	buf[100 + 1];
	char	table[] = "0123456789";
	char	*head;
	int		sign = 1;
	char	*set_buf_head = set_buf;

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
	
	while (*head)
		*set_buf++ = *head++;
	*set_buf = '\0';
	return set_buf - set_buf_head;
}
