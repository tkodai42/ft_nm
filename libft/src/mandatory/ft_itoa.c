#include "libft.h"

char	*ft_itoa(int num)
{
	char	buf[100 + 1];
	char	*head;
	int		sign = 1;

	head = buf + 100;
	*head = '\0';
	if (num < 0)
		sign = -1;
	while (*head == '\0' || num != 0)
	{
		*--head = num % 10 * sign + '0';
		num /= 10;
	}
	if (sign == -1)
		*--head = '-';
	return ft_strdup(head);
}
