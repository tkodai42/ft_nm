#include <stdio.h>

const char *ret_message1(int flag)
{
	if (flag == 0)
		return "FLAG_0";
	if (flag == 1)
		return "FLAG_1";
	if (flag == 2)
		return "FLAG_2";
	if (flag == 3)
		return "FLAG_3";
	return "FLAG_ERROR";
}

int		main()
{
	const char	*error_msg[5];

	for (int i = 0; i < 5; i++)
	{
		error_msg[i] = ret_message1(i);
	}
	for (int i = 0; i < 5; i++)
	{
		printf("%s\n", error_msg[i]);
	}
}
