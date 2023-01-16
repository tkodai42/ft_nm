#include "libft.h"

void	main2()
{
	t_list_node	*head = NULL;

	// ===== LIST SIZE =====
	printf("list size: %d\n", ft_list_size(head));


	// ===== PUSH =====
	ft_list_add_back_raw(&head, (void *)4);
	ft_list_add_back_raw(&head, (void *)1);
	ft_list_add_back_raw(&head, (void *)6);
	ft_list_add_back_raw(&head, (void *)6);
	ft_list_add_back_raw(&head, (void *)3);
	ft_list_add_back_raw(&head, (void *)9);

	printf("list size: %d\n", ft_list_size(head));

	// ===== SHOW =====
	ft_list_show(head, ft_list_show_func_ptr_int);
	printf("\n");

	// ===== LIST =====
	printf("rev 0: ");
	ft_list_sort(&head, ft_list_comp_func_ptr_int, 0);
	ft_list_show(head, ft_list_show_func_ptr_int);
	printf("\n");

	printf("rev 1: ");
	ft_list_sort(&head, ft_list_comp_func_ptr_int, 1);
	ft_list_show(head, ft_list_show_func_ptr_int);
	printf("\n");
}

int		main()
{
	main2();
	//system("leaks a.out");
}




