#include <stdio.h>

int		g_uninit;
int		g_init = 42;

static int	g_static_uninit;
static int	g_static_init = 0;

void	f1()
{
	static char static_str[] = "HELLO";
	
	printf("HELLO \n");
	printf("WORLD!\n");
}

int		main()
{
	f1();
}

