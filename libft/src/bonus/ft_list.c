#include "libft.h"

int		ft_list_size(t_list_node *lst)
{
	t_list_node		*next_list;
	int				i;

	if (lst == NULL)
		return (0);
	i = 1;
	next_list = lst;
	while (next_list->next != NULL)
	{
		i++;
		next_list = next_list->next;
	}
	return (i);
}

t_list_node	*ft_list_new(void *content)
{
	t_list_node	*new_lst;

	if (!(new_lst = malloc(sizeof(t_list_node))))
		return (NULL);
	new_lst->content = content;
	new_lst->next = NULL;
	new_lst->prev = NULL;
	return (new_lst);
}

t_list_node	*ft_list_last(t_list_node *lst)
{
	t_list_node	*ret_list;

	if (!lst)
		return (NULL);
	ret_list = lst;
	while (ret_list->next != NULL)
	{
		ret_list = ret_list->next;
	}
	return (ret_list);
}

void	ft_list_add_back(t_list_node **lst, t_list_node *new)
{
	t_list_node	*tmp;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = ft_list_last(*lst);
	tmp->next = new;
	new->prev = tmp;
}

void	ft_list_add_back_raw(t_list_node **lst, void *content)
{
	t_list_node	*tmp;
	t_list_node *new;

	if (lst == NULL)
		return ;
	new = ft_list_new(content);
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = ft_list_last(*lst);
	tmp->next = new;
	new->prev = tmp;

}

void	ft_list_clear(t_list_node **lst, void (*del)(void*))
{
	t_list_node		*tmp_lst;

	while (*lst)
	{
		tmp_lst = *lst;
		del((*lst)->content);
		*lst = tmp_lst->next;
		free(tmp_lst);
	}
}

/* show function ptr */
void	ft_list_show_func_ptr_int(void *c)
{
	printf("[%d]", (int)c);
}



void	ft_list_show(t_list_node *head, void (*show)(void*))
{
	while (head)
	{
		show(head->content);	
		head = head->next;
	}
}

/* comp function ptr */
int		ft_list_comp_func_ptr_int(void *c1, void *c2)
{
	return (int)c1 < (int)c2;
}


void	ft_list_sort(t_list_node **lst, int (*comp)(void*, void*), int is_rev)
{
	int			size;
	int			index = 0;
	t_list_node	*tmp;
	t_list_node **ary;

	if (lst == NULL || *lst == NULL)
		return ;
	size = ft_list_size(*lst);
	ary = malloc(sizeof(t_list_node) * size);

	//--- fill ---
	tmp = *lst;
	index = 0;
	while (tmp)
	{
		ary[index++] = tmp;
		tmp = tmp->next;
	}
	//--- sort ---
	index = 0;
	while (index + 1 < size)
	{
		(void)is_rev;
		//if ((is_rev && comp(ary[index]->content, ary[index + 1]->content)) ||
		//	(!is_rev && comp(ary[index + 1]->content, ary[index]->content)))
		if ((!is_rev && comp(ary[index]->content, ary[index + 1]->content) > 0) ||
			(is_rev && comp(ary[index + 1]->content, ary[index]->content) > 0))
		{
			tmp = ary[index];
			ary[index] = ary[index + 1];
			ary[index + 1] = tmp;
			index = 0;
			continue ;
		}
		index++;
	}
	//--- refill ---
	index = 0;
	ary[0]->prev = NULL;
	ary[size - 1]->next = NULL;
	while (index + 1 < size)
	{
		ary[index]->next = ary[index + 1];
		ary[index + 1]->prev = ary[index];
		index++;
	}
	*lst = ary[0];
}
