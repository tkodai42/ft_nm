#include "libft.h"

void	main2()
{
	t_queue q_tmp;
	t_queue *q = &q_tmp;

	queue_constructor(q);
	queue_push(q, (void *)3);
	queue_push(q, (void *)4);
	queue_push(q, (void *)5);
	queue_push(q, (void *)6);
	printf("size %d\n", queue_size(q));

	while (queue_size(q) != 0)
	{
		int num = (int)queue_front(q);
		queue_pop(q);
		printf("front %d\n", num);

	}

	//queue_destructor(q);
}

int		main()
{
	main2();
	system("leaks a.out");
}




